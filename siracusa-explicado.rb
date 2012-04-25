#!/usr/bin/env ruby
# encoding: utf-8
# Ver http://www.programando.org/blog/2012/04/desafio-2012-04-el-problema-de-siracusa/
#
# por @aldrinmartoq

# caché de saltos, según tabla de @lnds.
# Si tabulamos hasta n=4 no hay necesidad de programar casos raros.
# 1: 4,2,1.           => 3
# 2: 1.               => 1
# 3: 10,5,16,8,4,2,1  => 7
# 4: 2,1.             => 2
$c = [0,3,1,7,2]

# retorna el número de saltos para el número i-ésimo
def s(i)
  # si está en cache, retornamos caché
  return $c[i] if $c[i]
  
  # si no, calculamos recursivamente
  b = s(i.even? ? i/2 : i*3+1) + 1
  
  # guardamos resultado de saltos en caché, ajustar según cantidad de RAM:
  # 100.000.000 es aprox 1GiB en mi tarro
  $c[i] = b if i < 100_000_000
  
  # ruby siempre retorna el último resultado, pero jruby requiere esta línea
  return b
end

# (1..x) itera';
#   map crea lista con elementos del bloque
#     each_with_index.max.[1] obtiene el índice del mayor elemento en la lista
puts (1..ARGV[0].to_i).map { |i| s(i) }.each_with_index.max.[1] + 1