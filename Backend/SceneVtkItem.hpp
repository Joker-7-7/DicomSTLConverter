#pragma once

#include "SceneVtkData.hpp"
#include "Backend/ThirdParty/QQuickVtkItem.h"

class SceneVtkItem : public QQuickVtkItem
{
    Q_OBJECT
public:

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;

    /**
     * Opens file button click
     */
    Q_INVOKABLE void OnOpenFileClicked(QString singleFile);

    /**
     * Open file button click
     */
    Q_INVOKABLE void OnOpenDirectoryClicked(QString directory);

    /**
     * Reset camera button click
     */
    Q_INVOKABLE void OnResetCameraClicked();

    /**
     * Teeth Config button click
     */
    Q_INVOKABLE void OnTeethConfigClicked();

    /**
     * Solid Config button click
     */
    Q_INVOKABLE void OnSolidConfigClicked();

    /**
     * Skin Config button click
     */
    Q_INVOKABLE void OnSkinConfigClicked();

    /**
     * Converts DICOM model to STL button click
     */
    Q_INVOKABLE void OnConvertToSTL();

    /**
     * Updates volume parameters when moving the slider
     * 
     * @param value      The value to update
     * @param sliderType The slider type (W or L)
     */
    Q_INVOKABLE void OnSliderChanged(int value, QString sliderType);

signals:
    void showMessageBox();
public:

    SceneVtkData* sceneData;

};
