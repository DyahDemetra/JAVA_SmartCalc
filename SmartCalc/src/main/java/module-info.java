module school21.smartcalc.application.smartcalc {
    requires javafx.controls;
    requires javafx.fxml;


    opens school21.smartcalc.application.smartcalc to javafx.fxml;
    exports school21.smartcalc.application.smartcalc;
}