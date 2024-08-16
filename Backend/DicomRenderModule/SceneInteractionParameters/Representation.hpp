#ifndef REPRESENTATION_HPP
#define REPRESENTATION_HPP

#include <vtkBoxWidget2.h>
#include <vtkNew.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkPlanes.h>
#include <vtkImageReader2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkBoxRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkImageData.h>


/**
 * A class that includes all application representation objects
 */
class Representation final
{
public:
	/**
	 * Dynamic orientation axis
	 */
	vtkNew<vtkCameraOrientationWidget> cameraAxisOrientManipulator;

	/**
	 * Ctor.
	 */
	Representation(vtkRenderWindowInteractor* interactor, vtkRenderer* renderer);
};

#endif
