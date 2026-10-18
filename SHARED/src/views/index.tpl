<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Calculadora C + PHP</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css">
</head>
<body>
  <div class="container m-4 p-4">

    <div class="row content-align-center">

    <h1>Calculadora usando biblioteca C</h1>

    <form method="POST" class="form" role="form">
        <div class="form-group">
        <label class="form-label">Primeiro número:</label><br>
	<input class="form-control" type="number" step="any" name="a" value="<?=$_REQUEST['a']?? ''?>" required>
        </div>

        <div class="form-group">
        <label class="form-label">Segundo número:</label>
	<input class="form-control" type="number" step="any" name="b" value="<?=$_REQUEST['b']?? ''?>" required>
        </div>

        <div class="form-group">
        <label class="form-label">Operação:</label><br>
        <select class="form-control" name="op" value="<?=$_REQUEST['op']?? ''?>" >
            <option selected value="">Escolha uma operação...</option>
            <option value="somar">Somar</option>
            <option value="subtrair">Subtrair</option>
            <option value="multiplicar">Multiplicar</option>
            <option value="dividir">Dividir</option>
	</select>
        </div>

        <button class="btn btn-primary" type="submit">Calcular</button>
    </form>


    <?php if ($resultado !== null): ?>
         
        <h3 class="alert alert-success m-2">Resultado: <?= $resultado ?></h3>
    <?php endif; ?>

     </div>


   <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js" defer></script>
</body>
</html>