#ifndef LAYERS_CONFIGURATION_HPP
#define LAYERS_CONFIGURATION_HPP

#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

namespace LayersConfiguration
{
	/**
	 * Function to set color function and opacity function for volume model
	 * 
	 * @param volumeProperty The volume parameters that change
	 */
	void SetColorAndOpacityFunction(vtkVolumeProperty* volumeProperty, double wl, double ww);
}

#endif
