<?php
/*********************************************************
 * Usando shared library C em PHP
 * @author: Wanderlei Silva do Carmo
 *********************************************************/

$ffi = FFI::cdef(
    "
    double somar(double a, double b);
    double subtrair(double a, double b);
    double multiplicar(double a, double b);
    double dividir(double a, double b);
    ",
    __DIR__ . "/lib/libminha_lib.so"
);

echo "Digite o primeiro número: ";
$a = floatval(trim(fgets(STDIN)));

echo "Digite o segundo número: ";
$b = floatval(trim(fgets(STDIN)));

echo "\nEscolha a operação:
1 - Somar
2 - Subtrair
3 - Multiplicar
4 - Dividir
Opção: ";

$op = intval(trim(fgets(STDIN)));

switch ($op) {
    case 1:
        $resultado = $ffi->somar($a, $b);
        break;
    case 2:
        $resultado = $ffi->subtrair($a, $b);
        break;
    case 3:
        $resultado = $ffi->multiplicar($a, $b);
        break;
    case 4:
        $resultado = $ffi->dividir($a, $b);
        break;
    default:
        echo "Opção inválida\n";
        exit;
}

echo "\nResultado: $resultado\n";
