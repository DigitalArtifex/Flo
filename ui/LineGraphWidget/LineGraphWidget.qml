import QtQuick 2.15
import QtGraphs

Item {
    GraphsView {
        id: lineGraphView
        marginLeft: 4
        marginBottom: -4
        marginRight: 30

        Connections {
            target: LineGraphData

            function onDateMinimumChanged() {
                dateTimeAxis.min = LineGraphData.dateMinimum
            }

            function onDateMaximumChanged() {
                dateTimeAxis.max = LineGraphData.dateMaximum
            }

            function onValueMinimumChanged() {
                var range = LineGraphData.valueMinimum + LineGraphData.valueMaximum
                var tickInterval = range / 5

                valueAxis.tickInterval = tickInterval
                valueAxis.min = LineGraphData.valueMinimum
            }

            function onValueMaximumChanged() {
                var range = LineGraphData.valueMinimum + LineGraphData.valueMaximum
                var tickInterval = range / 5

                valueAxis.tickInterval = tickInterval
                valueAxis.max = LineGraphData.valueMaximum
            }

            function onSeriesAdded(series) {
                lineGraphView.addSeries(series)
            }

            function onSeriesRemoved(series) {
                lineGraphView.removeSeries(series)
            }

            function onGridMainColorChanged() {
                graphsTheme.grid.mainColor = LineGraphData.gridMainColor
            }

            function onGridSubColorChanged() {
                graphsTheme.grid.subColor = LineGraphData.gridSubColor
            }

            function onAxisYMainColorChanged() {
                graphsTheme.axisY.mainColor = LineGraphData.axisYMainColor
            }

            function onAxisYSubColorChanged() {
                graphsTheme.axisY.subColor = LineGraphData.axisYSubColor
            }

            function onAxisXMainColorChanged() {
                graphsTheme.axisX.mainColor = LineGraphData.axisXMainColor
            }

            function onAxisXSubColorChanged() {
                graphsTheme.axisX.subColor = LineGraphData.axisXSubColor
            }

            function onValueLabelFormatChanged() {
                valueAxis.labelFormat = LineGraphData.valueLabelFormat
            }
        }

        anchors.fill: parent
        theme: GraphsTheme {
            id: graphsTheme
            colorScheme: GraphsTheme.ColorScheme.Dark
            seriesColors: ["#226666", "#2D882D", "#AA3939", "#AA6C39"]
            grid.mainColor: "#ccccff"
            grid.subColor: "#eeeeff"
            axisY.mainColor: "#ccccff"
            axisY.subColor: "#eeeeff"
            GraphTransition {
                GraphPointAnimation { duration: 300 }
            }
        }

        axisX: DateTimeAxis {
            property var locale: Qt.locale()
            id: dateTimeAxis
            lineVisible: false
            tickInterval: 4
            labelFormat: "HH:mm:ss"
        }

        axisY: ValueAxis {
            id: valueAxis
            labelDecimals: 2
            min: 0
            max: 10
            subTickCount: 2
            tickInterval: 5
        }

        Component.onCompleted: {
            graphsTheme.axisX.subColor = LineGraphData.axisXSubColor
            graphsTheme.axisX.mainColor = LineGraphData.axisXMainColor

            graphsTheme.axisY.subColor = LineGraphData.axisYSubColor
            graphsTheme.axisY.mainColor = LineGraphData.axisYMainColor

            graphsTheme.grid.subColor = LineGraphData.gridSubColor
            graphsTheme.grid.mainColor = LineGraphData.gridMainColor
        }
    }
}
