package school21.smartcalc.application.smartcalc;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Spinner;
import javafx.scene.control.SpinnerValueFactory;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.scene.input.ScrollEvent;
import javafx.scene.input.MouseEvent;

import java.text.DecimalFormat;

public class GraphWindow {
    private HelloController controller;
    private String function;
    public GraphWindow(HelloController controller, String function) {
        this.controller = controller;
        this.function = function;
    }

    private double xOffset = 0;
    private double yOffset = 0;

    public void show() {
        NumberAxis xAxis = new NumberAxis(-50, 50, 1);
        NumberAxis yAxis = new NumberAxis(-50, 50, 1);
        xAxis.setLabel("X Axis");
        yAxis.setLabel("Y Axis");

        LineChart<Number, Number> lineChart = new LineChart<>(xAxis, yAxis);
        lineChart.setTitle("Graph of the Function");

        Spinner<Double> xMinSpinner = new Spinner<>();
        Spinner<Double> xMaxSpinner = new Spinner<>();
        Spinner<Double> yMinSpinner = new Spinner<>();
        Spinner<Double> yMaxSpinner = new Spinner<>();

        xMinSpinner.setValueFactory(new SpinnerValueFactory.DoubleSpinnerValueFactory(-1000000, 1000000, -50, 1));
        xMaxSpinner.setValueFactory(new SpinnerValueFactory.DoubleSpinnerValueFactory(-1000000, 1000000, 50, 1));
        yMinSpinner.setValueFactory(new SpinnerValueFactory.DoubleSpinnerValueFactory(-1000000, 1000000, -50, 1));
        yMaxSpinner.setValueFactory(new SpinnerValueFactory.DoubleSpinnerValueFactory(-1000000, 1000000, 50, 1));

        xMinSpinner.valueProperty().addListener((obs, oldValue, newValue) -> xAxis.setLowerBound(newValue));
        xMaxSpinner.valueProperty().addListener((obs, oldValue, newValue) -> xAxis.setUpperBound(newValue));
        yMinSpinner.valueProperty().addListener((obs, oldValue, newValue) -> yAxis.setLowerBound(newValue));
        yMaxSpinner.valueProperty().addListener((obs, oldValue, newValue) -> yAxis.setUpperBound(newValue));

        Button createGraphButton = new Button("Create Graph");
        createGraphButton.setOnAction(event -> {
            lineChart.getData().clear();
            drawGraph(lineChart, xAxis, yAxis, xMinSpinner.getValue(), xMaxSpinner.getValue());
        });

        HBox controls = new HBox(10, xMinSpinner, xMaxSpinner, yMinSpinner, yMaxSpinner, createGraphButton);
        BorderPane root = new BorderPane();
        root.setCenter(lineChart);
        root.setBottom(controls);

        Stage graphStage = new Stage();
        Scene scene = new Scene(root, 800, 600);
        graphStage.setTitle("Graph");
        graphStage.setScene(scene);
        graphStage.show();
    }

    private void drawGraph(LineChart<Number, Number> lineChart, NumberAxis xAxis, NumberAxis yAxis, double xMinValue, double xMaxValue) {

        XYChart.Series<Number, Number> series = new XYChart.Series<>();
        series.setName("f(x)");
        double h = (xMaxValue + Math.abs(xMinValue)) / 3500;

        for (double i = xMinValue; i < xMaxValue; i+=h) {
            String tempX = String.format("%.3f", i).replace(',','.');
            double y = controller.calculateWrapper(function, tempX);
            series.getData().add(new XYChart.Data<>(i, y));
        }

        lineChart.getData().add(series);

        lineChart.setOnScroll((ScrollEvent event) -> {
            if (event.getDeltaY() != 0) {
                double zoomFactor = (event.getDeltaY() > 0) ? 1.1 : 0.9;
                xAxis.setLowerBound(xAxis.getLowerBound() * zoomFactor);
                xAxis.setUpperBound(xAxis.getUpperBound() * zoomFactor);
                yAxis.setLowerBound(yAxis.getLowerBound() * zoomFactor);
                yAxis.setUpperBound(yAxis.getUpperBound() * zoomFactor);
            }
        });

        lineChart.setOnMousePressed((MouseEvent event) -> {
            xOffset = event.getX();
            yOffset = event.getY();
        });

        lineChart.setOnMouseDragged((MouseEvent event) -> {
            double deltaX = (event.getX() - xOffset) / 10;
            double deltaY = (event.getY() - yOffset) / 10;

            xAxis.setLowerBound(xAxis.getLowerBound() - deltaX);
            xAxis.setUpperBound(xAxis.getUpperBound() - deltaX);
            yAxis.setLowerBound(yAxis.getLowerBound() + deltaY);
            yAxis.setUpperBound(yAxis.getUpperBound() + deltaY);

            xOffset = event.getX();
            yOffset = event.getY();
        });
    }
}
