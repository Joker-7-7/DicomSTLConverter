#include "SceneVtkItem.hpp"
#include "DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(SceneVtkData);

QQuickVtkItem::vtkUserData SceneVtkItem::initializeVTK(vtkRenderWindow* renderWindow) {
    auto vtkScene = vtkNew<SceneVtkData>();
    sceneData = vtkScene;
    sceneData->InitSceneVTKData(renderWindow);
    return vtkScene;
}

void SceneVtkItem::OnOpenDirectoryClicked(QString directory) {
    std::function<void(vtkRenderWindow *, vtkUserData)> openDirectory([this, directory](vtkRenderWindow*, const vtkUserData&) {
        if (!sceneData->OpenDirectory(directory)) {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(openDirectory);
}

void SceneVtkItem::OnOpenFileClicked(QString singleFile) {
    std::function<void(vtkRenderWindow*, vtkUserData)> openFile([this, singleFile](vtkRenderWindow*, const vtkUserData&) {
        if (!sceneData->OpenSingleFile(singleFile)) {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(openFile);
}

void SceneVtkItem::OnResetCameraClicked() {
    std::function<void(vtkRenderWindow*, vtkUserData)> zoomExtent([this](vtkRenderWindow*, const vtkUserData&) {
        sceneData->ZoomToExtent();
    });
    QQuickVtkItem::dispatch_async(zoomExtent);
}

void SceneVtkItem::OnSliderChanged(int value, QString sliderType) {
    std::function<void(vtkRenderWindow*, vtkUserData)> sliderChanged([this, value, sliderType](vtkRenderWindow*, const vtkUserData&) {
        if (sliderType == "W") {
            sceneData->viewSettings.wLevel = value;
        }
        else if (sliderType == "L") {
            sceneData->viewSettings.lLevel = value;
        }
        LayersConfiguration::SetColorAndOpacityFunction(sceneData->volumeProperty, sceneData->viewSettings.lLevel, sceneData->viewSettings.wLevel);
    });
    QQuickVtkItem::dispatch_async(sliderChanged);
}

void SceneVtkItem::OnTeethConfigClicked() {
    std::function<void(vtkRenderWindow*, vtkUserData)> teethConfig([this](vtkRenderWindow*, const vtkUserData&) {
        SceneVtkData::ViewSettings teethSettings{ 1830.0, 140.0 };
        LayersConfiguration::SetColorAndOpacityFunction(sceneData->volumeProperty, teethSettings.lLevel, teethSettings.wLevel);
     });
    QQuickVtkItem::dispatch_async(teethConfig);
}

void SceneVtkItem::OnSolidConfigClicked() {
    std::function<void(vtkRenderWindow*, vtkUserData)> solidConfig([this](vtkRenderWindow*, const vtkUserData&) {
        SceneVtkData::ViewSettings solidSettings{ 1560.0, 250.0 };
        LayersConfiguration::SetColorAndOpacityFunction(sceneData->volumeProperty, solidSettings.lLevel, solidSettings.wLevel);
    });
    QQuickVtkItem::dispatch_async(solidConfig);
}

void SceneVtkItem::OnSkinConfigClicked() {
    std::function<void(vtkRenderWindow*, vtkUserData)> skinConfig([this](vtkRenderWindow*, const vtkUserData&) {
        SceneVtkData::ViewSettings skinSettings{ 1560.0, 250.0 };
        LayersConfiguration::SetColorAndOpacityFunction(sceneData->volumeProperty, skinSettings.lLevel, skinSettings.wLevel);
    });
    QQuickVtkItem::dispatch_async(skinConfig);
}

void SceneVtkItem::OnConvertToSTL() {
    std::function<void(vtkRenderWindow*, vtkUserData)> convertToSTL([this](vtkRenderWindow*, const vtkUserData&) {
        sceneData->ConvertToSTL();
    });
    QQuickVtkItem::dispatch_async(convertToSTL);
}
