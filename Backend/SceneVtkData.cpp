#include "SceneVtkData.hpp"
#include "Backend/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkGlobFileNames.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkRenderWindow.h>
#include <vtkSTLWriter.h>
#include <vtkDecimatePro.h>

namespace
{
    vtkSmartPointer<vtkPolyData> ReducePolyDataResolution(vtkSmartPointer<vtkPolyData> polyData, double reductionFactor)
    {
        // Create a vtkDecimatePro object
        vtkSmartPointer<vtkDecimatePro> decimate = vtkSmartPointer<vtkDecimatePro>::New();
        decimate->SetInputData(polyData);

        // Set the reduction factor (the target percentage of the original triangles to retain)
        decimate->SetTargetReduction(reductionFactor); // 0.5 means 50% reduction
        decimate->PreserveTopologyOn(); // Preserve the overall shape

        // Update the decimation process
        decimate->Update();

        // Get the decimated output
        return decimate->GetOutput();
    }

    vtkSmartPointer<vtkPolyData> ExtractSurface(vtkSmartPointer<vtkImageData> imageData, double isoValue)
    {
        // Create the vtkMarchingCubes object
        vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();

        // Set the input data (vtkImageData in this case)
        marchingCubes->SetInputData(imageData);

        // Set the isosurface value (threshold value)
        marchingCubes->SetValue(0, isoValue);

        // Update the filter to generate the surface
        marchingCubes->Update();

        // Extract the output as vtkPolyData
        vtkSmartPointer<vtkPolyData> polyData = ReducePolyDataResolution(marchingCubes->GetOutput(), 0.5);

        return polyData;
    }
}

SceneVtkData::SceneVtkData() :
    _backgroundColor{0.3, 0.3, 0.3}
{
}

void SceneVtkData::InitSceneVTKData(vtkRenderWindow* renderWindow) {
#ifndef _DEBUG
    vtkObject::GlobalWarningDisplayOff();
#endif

    _renderWindow = renderWindow;
    SetupRender();
    SetupGPU();

    CreateRepresentations();
}

void SceneVtkData::SetupRender() {
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    style->SetDefaultRenderer(_renderer);

    _renderWindow->GetInteractor()->SetInteractorStyle(style);
    _renderWindow->SetSize(_renderWindow->GetScreenSize());
    _renderWindow->AddRenderer(_renderer);
    _renderWindow->SetWindowName("MainWindow");

    _renderer->SetBackground(_backgroundColor);
}

void SceneVtkData::SetupGPU() const noexcept {
    // Setup Volume property
    vtkNew<vtkColorTransferFunction> m_ptrColorFunction;
    vtkNew<vtkPiecewiseFunction> m_ptrOpacityFunction;
    volumeProperty->SetColor(m_ptrColorFunction);
    volumeProperty->SetScalarOpacity(m_ptrOpacityFunction);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.1);
    volumeProperty->SetDiffuse(0.8);
    volumeProperty->SetSpecular(0.25);
    volumeProperty->SetSpecularPower(40);

    LayersConfiguration::SetColorAndOpacityFunction(volumeProperty, viewSettings.lLevel, viewSettings.wLevel);
    _volume->SetProperty(volumeProperty);
}

void SceneVtkData::AddDataSet(vtkSmartPointer<vtkImageReader2> reader) {
    RemoveDataSet();

    SetupReader(reader);

    vtkNew<vtkGPUVolumeRayCastMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->SetMaximumImageSampleDistance(1.0);

    _volume->SetProperty(volumeProperty);
    _volume->SetMapper(mapper);

    _renderer->AddVolume(_volume);
    _renderer->ResetCamera();
}

void SceneVtkData::RemoveDataSet() const {
    vtkProp *volume = _renderer->GetVolumes()->GetLastProp();
    if (volume != nullptr) {
        _renderer->RemoveVolume(volume);
    }
}

void SceneVtkData::SetupReader(vtkSmartPointer<vtkImageReader2> reader) {
    _reader = std::move(reader);

    vtkNew<vtkDICOMReader> newReaderCopy;
    auto dicomReader = dynamic_cast<vtkDICOMReader*>(reader.Get());
    if (dicomReader->GetFileName() != nullptr)
    {
        newReaderCopy->SetFileName(dicomReader->GetFileName());
    }
    else
    {
        newReaderCopy->SetFileNames(dicomReader->GetFileNames());
    }
    newReaderCopy->SetMemoryRowOrderToFileNative();
    newReaderCopy->Update();
}

bool SceneVtkData::OpenDirectory(QString directory) {
    vtkSmartPointer<vtkImageReader2> dataSet = nullptr;
    QString directoryName = directory.remove(0, 8);

    auto globFileNames = vtkSmartPointer<vtkGlobFileNames>::New();
    globFileNames->SetDirectory(directoryName.toStdString().c_str());
    globFileNames->AddFileNames("*.dcm");

    auto directoryReader = vtkSmartPointer<vtkDICOMDirectory>::New();
    directoryReader->RequirePixelDataOn();
    directoryReader->SetInputFileNames(globFileNames->GetFileNames());
    directoryReader->Update();

    if (directoryReader->GetNumberOfSeries() == 0) {
        return false;
    }

    vtkNew<vtkDICOMReader> reader;
    reader->SetFileNames(directoryReader->GetFileNamesForSeries(0));
    reader->SetMemoryRowOrderToFileNative();
    reader->Update();

    return CheckReader(std::move(reader), dataSet);
}

bool SceneVtkData::OpenSingleFile(QString singleFile) {
    vtkSmartPointer<vtkImageReader2> dataSet = nullptr;
    QString fileName = singleFile.remove(0, 8);

    vtkNew<vtkDICOMReader> fileReader;
    fileReader->SetFileName(fileName.toStdString().c_str());
    fileReader->SetMemoryRowOrderToFileNative();
    fileReader->Update();

    return CheckReader(std::move(fileReader), dataSet);
}

bool SceneVtkData::CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet) {
    if (reader->GetErrorCode() == 0) {
        dataSet = reader;
    }

    if (dataSet) {
        AddDataSet(dataSet);
        return true;
    }

    return false;
}

void SceneVtkData::ZoomToExtent() const noexcept {
    _renderer->ResetCamera();
}

void SceneVtkData::CreateRepresentations() noexcept {
    _representation = std::make_shared<Representation>(_renderWindow->GetInteractor(), _renderer.Get());
}

void SceneVtkData::ConvertToSTL() {
    auto mapper = vtkVolumeMapper::SafeDownCast(_volume->GetMapper());
    vtkSmartPointer<vtkImageData> imageData = vtkImageData::SafeDownCast(mapper->GetInput());
    vtkSmartPointer<vtkPolyData> polyData = ExtractSurface(imageData, viewSettings.lLevel);
    vtkNew<vtkSTLWriter> stlWriter;
    stlWriter->SetFileName("model.stl");
    stlWriter->SetInputData(polyData);
    stlWriter->Write();
}
