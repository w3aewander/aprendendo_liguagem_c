import ctypes

lib = ctypes.CDLL("./lib/libminha_lib.so")

# Define tipos dos parâmetros
lib.somar.argtypes = [ctypes.c_int, ctypes.c_double]
lib.multiplicar.argtypes = [ ctypes.c_double, ctypes.c_double]

# Define tipo de retorno
lib.somar.restype = ctypes.c_double
lib.multiplicar.restype = ctypes.c_double

resultado = lib.somar(10,40)
resultado2 = lib.multiplicar(9,6)

print(resultado)  # 50
print(resultado2) # 54