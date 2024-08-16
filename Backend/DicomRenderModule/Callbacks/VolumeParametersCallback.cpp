#include "VolumeParametersCallback.hpp"
#include <vtkPolyData.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
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

vtkButtonJitteringModeCallback::vtkButtonJitteringModeCallback() {
    volume = nullptr;
    isJitteringMode = true;
}


void vtkButtonJitteringModeCallback::Execute(vtkObject* caller, unsigned long, void*) {
    auto mapper = vtkVolumeMapper::SafeDownCast(volume->GetMapper());
    vtkSmartPointer<vtkImageData> imageData = vtkImageData::SafeDownCast(mapper->GetInput());
    double isoValue = 2000;
    vtkSmartPointer<vtkPolyData> polyData = ExtractSurface(imageData, isoValue);
    vtkNew<vtkSTLWriter> stlWriter;
    stlWriter->SetFileName("model.stl");
    stlWriter->SetInputData(polyData);
    stlWriter->Write();
}
