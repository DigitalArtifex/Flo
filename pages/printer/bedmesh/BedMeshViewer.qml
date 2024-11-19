//Modified version of SurfaceSpectrogram.qml

// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtGraphs
import Qt3D.Core
import Qt3D.Render
import Qt3D.Input
import Qt3D.Logic
import Qt3D.Extras
import Qt3D.Animation
import QtQuick.Scene2D
import QtQuick.Scene3D

Rectangle {
    id: spectrogramView
    color: customTheme.backgroundColor

    property real buttonWidth: (spectrogramView.width - 35) / 2

    Connections {
        target: BedMeshData

        function onDataChanged() {
            BedMeshData.update(surfaceSeries)
        }
    }

    Item {
        id: surfaceView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: legend.left
        anchors.bottom: footer.top

        Gradient {
            id: surfaceGradient

            GradientStop { position: 0.0; color: "#0031A2" }
            GradientStop { position: 0.25; color: "#6800A1" }
            GradientStop { position: 0.5; color: "#00AF41" }
            GradientStop { position: 0.75; color: "#F22A00" }
            GradientStop { position: 1.0; color: "#F2AC00" }
        }

        Value3DAxis {
            id: xAxis
            segmentCount: 8
            labelFormat: "%d"
            title: "X"
            titleVisible: true
            titleFixed: true
        }

        Value3DAxis {
            id: yAxis
            segmentCount: 8
            labelFormat: "%d"
            title: "Y"
            titleVisible: true
            titleFixed: true
        }

        Value3DAxis {
            id: zAxis
            segmentCount: 5
            labelFormat: "%F"
            title: "Z"
            titleVisible: true
            titleFixed: true
            min: -0.5
            max: 0.5
        }

        GraphsTheme {
            id: customTheme
            colorScheme: GraphsTheme.ColorScheme.Dark
            baseColors: [ Color { color: "yellow" } ]
            plotAreaBackgroundVisible: false
            backgroundVisible: false
            labelBorderVisible: false
            labelBackgroundVisible: false
            labelTextColor: "white"
            backgroundColor: _theme_graphBackgroundColor
            plotAreaBackgroundColor: _theme_graphPlotAreaBackgroundColor
        }

        //! [0]
        Surface3D {
            id: surfaceGraph
            anchors.fill: parent

            // Don't show specular spotlight as we don't want it to distort the colors
            lightStrength: 0.0
            ambientLightStrength: 1.0

            Surface3DSeries {
                id: surfaceSeries
                shading: Surface3DSeries.Shading.Smooth
                drawMode: Surface3DSeries.DrawSurfaceAndWireframe
                baseGradient:  surfaceGradient
                colorStyle: GraphsTheme.ColorStyle.RangeGradient
                itemLabelFormat: "@yLabel"
            }
            //! [0]

            //! [1]
            // Remove the perspective and view the graph from top down to achieve 2D effect
            orthoProjection: false
            cameraPreset: Graphs3D.CameraPreset.IsometricRight
            //! [1]

            //! [2]
            flipHorizontalGrid: false
            //! [2]

            //! [4]
            radialLabelOffset: 0.01
            //! [4]

            //! [5]
            rotationEnabled: !surfaceGraph.orthoProjection
            //! [5]

            theme: customTheme
            shadowQuality: Graphs3D.ShadowQuality.None
            selectionMode: Graphs3D.SelectionFlag.ItemAndColumn
            axisX: xAxis
            axisY: zAxis
            axisZ: yAxis

            aspectRatio: 2.0
            horizontalAspectRatio: 1.0
            cameraZoomLevel: 80
            Component.onCompleted: BedMeshData.update(surfaceSeries)
        }
    }

    Item {
        id: legend
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        width: 100

        Rectangle {
            id: gradient
            anchors.margins: 20
            anchors.bottom: legend.bottom
            anchors.top: legend.top
            anchors.right: legend.right
            border.color: "black"
            border.width: 1
            width: 25
            rotation: 180
            gradient: surfaceGradient
        }

        Text {
            anchors.verticalCenter: gradient.bottom
            anchors.right: gradient.left
            anchors.margins: 2
            text: "%1mm".arg((surfaceGraph.axisY.min).toFixed(1))
            color: "#FFFFFF"
        }

        Text {
            anchors.verticalCenter: gradient.verticalCenter
            anchors.right: gradient.left
            anchors.margins: 2
            text: "%1mm".arg(((surfaceGraph.axisY.max + surfaceGraph.axisY.min) / 2).toFixed(1))
            color: "white"
        }

        Text {
            anchors.verticalCenter: gradient.top
            anchors.right: gradient.left
            anchors.margins: 2
            text: surfaceGraph.axisY.max.toFixed(1) + "mm"
            color: "white"
        }
    }

    Item
    {
        id: footer
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: legend.left
        anchors.bottom: parent.bottom
        height: 70

        Item
        {
            id: row1
            anchors.left: parent.left
            anchors.right: parent.right
            height: 35

            Text
            {
                id: footerLabel
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left

                anchors.margins: 10
                text: "Z Scale (" + zScaleSlider.value.toFixed(1) + "mm)";
                color: "white"
            }
        }

        Item
        {
            id: row2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: row1.bottom

            height: 35
            Text
            {
                id: sliderLowLabel
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left

                anchors.margins: 10
                text: "0.1"
                color: "white"
            }

            Slider
            {
                id: zScaleSlider
                from: 0.10000
                to: 2.0000
                value: 0.50000
                stepSize: 0.1000

                anchors.margins: 10
                anchors.left: sliderLowLabel.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: sliderHighLabel.left

                onValueChanged:
                {
                    surfaceGraph.axisY.min = (value * -1);
                    surfaceGraph.axisY.max = value;
                }
            }

            Text
            {
                id: sliderHighLabel
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: surfaceGridToggle.left

                anchors.margins: 10
                text: "2.0"
                color: "white"
            }

            Button {
                id: surfaceGridToggle
                anchors.margins: 5
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: 100
                text: "Grid"
                visible: !surfaceGraph.orthoProjection
                onClicked: {
                    if (surfaceSeries.drawMode & Surface3DSeries.DrawWireframe)
                        surfaceSeries.drawMode &= ~Surface3DSeries.DrawWireframe;
                    else
                        surfaceSeries.drawMode |= Surface3DSeries.DrawWireframe;
                }
            }
        }
    }
}
