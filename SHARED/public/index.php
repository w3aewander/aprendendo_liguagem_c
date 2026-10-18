<?php

// Carrega a biblioteca C
$ffi = FFI::cdef(
    "
    double somar(double a, double b);
    double subtrair(double a, double b);
    double multiplicar(double a, double b);
    double dividir(double a, double b);
    ",
    __DIR__ . "/../lib/libminha_lib.so"
);

$resultado = null;

if ($_SERVER["REQUEST_METHOD"] === "POST") {

    $a = floatval($_POST["a"]);
    $b = floatval($_POST["b"]);

    
    $op = $_POST["op"];

    switch ($op) {
        case "somar":
            $resultado = $ffi->somar($a, $b);
            break;
        case "subtrair":
            $resultado = $ffi->subtrair($a, $b);
            break;
        case "multiplicar":
            $resultado = $ffi->multiplicar($a, $b);
            break;
        case "dividir":
            // evitar divisão por zero.
            if ( $b != 0 ) 
                $resultado = $ffi->dividir($a, $b);
            else
                $resultado = "Divisão por zero  não permitido";
            break;
    }
}

// Start capturing the HTML file
ob_start();
include '../src/views/index.tpl';   // your HTML file
$pageContent = ob_get_clean(); // capture and clear buffer


// Display the final composed page
echo $pageContent;

?>



