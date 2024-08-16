#pragma once

#include "Backend//DicomRenderModule/SceneInteractionParameters/Representation.hpp"

#include <QString.h>

#include <vtkObject.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVolumeProperty.h>
#include <vtkImageReader2.h>
#include <vtkDICOMReader.h>

class SceneVtkData final : public vtkObject
{
public:
    struct ViewSettings final
    {
        int lLevel = 900;
        int wLevel = 300;
    };

    /**
     * Sliders value
     */
    ViewSettings viewSettings;

    /**
     * Represents the common properties for rendering a volume
     */
    vtkNew<vtkVolumeProperty> volumeProperty;

    vtkTypeMacro(SceneVtkData, vtkObject);
    static SceneVtkData* New();

    /**
     * Ctor. 
     */
    SceneVtkData();

    void InitSceneVTKData(vtkRenderWindow *renderWindow);

    /**
     * Adds a data set to the scene
     * 
     * @param dataSet The data set to add
     */
    void AddDataSet(vtkSmartPointer<vtkImageReader2> dataSet);

    /**
     * Setups renderer, _renderWindow, interactor
     */
    void SetupRender();

    /**
     * Setups vtkGPUVolumeRayCastMapper, vtkColorTransferFunction, vtkPiecewiseFunction
     */
    void SetupGPU() const noexcept;

    /**
     * Removes the data set from the scene
     */
    void RemoveDataSet() const;

    /**
     * Setups readers parameters for m_ptrReader and m_ptrPreReader
     */
    void SetupReader(vtkSmartPointer<vtkImageReader2> reader);

    /**
     * Creates all representations un the app
     */
    void CreateRepresentations() noexcept;

    /**
     * Zoom to the extent of the data set in the scene
     */
    void ZoomToExtent() const noexcept;

    /**
     * Opens single DICOM file
     * 
     * @param singleFile The path to single DICOM file
     * @return Error value code
     */
    [[nodiscard]] bool OpenSingleFile(QString singleFile);

    /**
     * Opens the directory with DICOM files
     *
     * @param directory The path to directory with DICOMs
     * @return Error value code
     */
    [[nodiscard]] bool OpenDirectory(QString directory);

    /**
     * Сheck the validity of the reader and add data to the scene if successful
     * @param reader Reader with selected file
     * @param dataSet Dataset for render
     * @return Error code: true - success, false - error
     */
    [[nodiscard]] bool CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet);

    void ConvertToSTL();

private:

    /**
     * Window background color
     */
    const double _backgroundColor[3];

    /**
     * Represents a volume (data & properties) in a rendered scene
     */
    vtkNew<vtkVolume> _volume;

    /**
     * Reader for first buffer
     */
    vtkSmartPointer<vtkImageReader2> _reader;

    /**
     * Is an object that controls the rendering process for objects
     */
    vtkNew<vtkRenderer> _renderer;

    /**
     * A window in a graphical user interface where renderers draw their images
     */
    vtkSmartPointer<vtkRenderWindow> _renderWindow;

    /**
     * Scene view elements
     */
    std::shared_ptr<Representation> _representation;
};
