#include "Representation.hpp"

Representation::Representation(vtkRenderWindowInteractor* interactor, vtkRenderer* renderer) {
    vtkNew<vtkInteractorStyleTrackballCamera> trackballStyle;
    interactor->SetInteractorStyle(trackballStyle);

    cameraAxisOrientManipulator->SetParentRenderer(renderer);
    cameraAxisOrientManipulator->SetInteractor(interactor);
    cameraAxisOrientManipulator->On();
}
