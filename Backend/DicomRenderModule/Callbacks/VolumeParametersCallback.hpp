#ifndef VOLUME_PARAMETERS_CALLBACK_HPP
#define VOLUME_PARAMETERS_CALLBACK_HPP


#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>
#include <vtkAbstractWidget.h>

/// <summary>
/// Callback for Jittering mode button
/// </summary>
class vtkButtonJitteringModeCallback final : public vtkAbstractWidget
{
public:
    vtkVolume* volume;
    bool isJitteringMode;

	vtkButtonJitteringModeCallback();

	static vtkButtonJitteringModeCallback* New();
	void Execute(vtkObject* caller, unsigned long, void*);
};

#endif
