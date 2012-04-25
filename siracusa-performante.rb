#!/usr/bin/env ruby
# encoding: utf-8
# Ver http://www.programando.org/blog/2012/04/desafio-2012-04-el-problema-de-siracusa/
# siracusa-cache -- mejora rendimiento aumentando caché de saltos
#
# Para ejecutar, prefiera jruby:
# $ time jruby -J-Xmx4096m siracusa-performante.rb 10000000
# 8400511
# 
# real  0m13.971s
# user  0m19.332s
# sys 0m0.406s
#
# por @aldrinmartoq

$c = [0,3,1,7,2]
def s(i)
  return $c[i] if $c[i]
  b = s(i.even? ? i/2 : i*3+1) + 1
  $c[i] = b if i < 10_000_000 # ajustar caché según RAM disponible
  return b # jruby requiere este return… *sigh*
end
puts (1..ARGV[0].to_i).map { |i| s(i) }.each_with_index.max.last + 1
