package school21.smartcalc.application.smartcalc;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

import java.io.File;

public class HelloController {
    @FXML
    private TextField xDisplay;
    @FXML
    private TextField funcDisplay;

    private String currentInput = "";
    private native double Calculate(String func, String valueOfX);
    public double calculateWrapper(String func, String x) {
        return Calculate(func, x);
    }

    static {
        System.load(new File("target/native-libs/model.dll").getAbsolutePath());
    }
    @FXML
    private void onNumberClick(javafx.event.ActionEvent event) {
        Button button = (Button) event.getSource();
        currentInput += button.getText();
        funcDisplay.setText(currentInput);
    }

    @FXML
    private void onEqualClick(javafx.event.ActionEvent event) {
        if (!currentInput.isEmpty()) {
            String x = xDisplay.getText();
            if (x.isEmpty()) {
                x = "0";
                xDisplay.setText("0");
            }
            double result;
            try {
                result = Calculate(funcDisplay.getText(), x);
                currentInput = String.valueOf(result);
                funcDisplay.setText(currentInput);
            } catch (RuntimeException e) {
                funcDisplay.setText(e.getMessage());
                currentInput="";
            }
        }
    }

    @FXML
    private void onClearClick(javafx.event.ActionEvent event) {
        currentInput = "";
        funcDisplay.setText("");
    }
    @FXML
    private void onGraphCreateClick() {
        GraphWindow graphWindow = new GraphWindow(this, funcDisplay.getText());
        graphWindow.show();
    }
}