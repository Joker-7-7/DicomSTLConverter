#include "LayersConfiguration.hpp"

namespace LayersConfiguration
{
    struct ColorFunctions final
    {
    public:
        vtkColorTransferFunction* color;
        vtkPiecewiseFunction* opacity;
        vtkPiecewiseFunction* gradient;

        ColorFunctions(vtkVolumeProperty* properties) noexcept :
            color{ properties->GetRGBTransferFunction() },
            opacity{ properties->GetScalarOpacity() },
            gradient{ properties->GetGradientOpacity() }
        {
            Reset();
        }
    private:
        void Reset() noexcept
        {
            color->RemoveAllPoints();
            opacity->RemoveAllPoints();
            gradient->RemoveAllPoints();
            gradient->AddPoint(0, 0.0);
            gradient->AddPoint(90, 0.5);
            gradient->AddPoint(100, 1.0);
        }
    };

    void SetColorAndOpacityFunction(vtkVolumeProperty* volumeProperty, double wl, double ww) {
        vtkColorTransferFunction* colorFunction = volumeProperty->GetRGBTransferFunction();
        colorFunction->RemoveAllPoints();
        vtkPiecewiseFunction* opacityFunction = volumeProperty->GetScalarOpacity();
        opacityFunction->RemoveAllPoints();

        colorFunction->SetColorSpaceToRGB();
        colorFunction->AddRGBPoint(wl - ww / 2.0, 0.0, 0.0, 0.0);
        colorFunction->AddRGBPoint(wl - ww / 2.0 + 94.0 * (ww / 255.0), 1.0, 21.0 / 255.0, 27.0 / 255.0);
        colorFunction->AddRGBPoint(wl - ww / 2.0 + 147.0 * (ww / 255.0), 1.0, 176.0 / 255.0, 9.0 / 255.0);
        colorFunction->AddRGBPoint(wl - ww / 2.0 + 201.0 * (ww / 255.0), 1.0, 241.0 / 255.0, 39.0 / 255.0);
        colorFunction->AddRGBPoint(wl - ww / 2.0 + 255.0 * (ww / 255.0), 1.0, 1.0, 1.0);

        opacityFunction->AddPoint(wl - ww / 2.0, 0.0);
        opacityFunction->AddPoint(wl + ww / 2.0, 1.0);
    }
}
