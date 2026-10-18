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
            $resultado = $ffi->dividir($a, $b);
            break;
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Calculadora C + PHP</title>
</head>
<body>
    <h2>Calculadora usando biblioteca C</h2>

    <form method="POST">
        <label>Primeiro número:</label><br>
        <input type="number" step="any" name="a" required><br><br>

        <label>Segundo número:</label><br>
        <input type="number" step="any" name="b" required><br><br>

        <label>Operação:</label><br>
        <select name="op">
            <option value="somar">Somar</option>
            <option value="subtrair">Subtrair</option>
            <option value="multiplicar">Multiplicar</option>
            <option value="dividir">Dividir</option>
        </select><br><br>

        <button type="submit">Calcular</button>
    </form>

    <?php if ($resultado !== null): ?>
        <h3>Resultado: <?= $resultado ?></h3>
    <?php endif; ?>
</body>
</html>

