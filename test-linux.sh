#!/bin/bash

# PROCEDIMIENTOS NUEVOS PARA LA ÚLTIMA ENTREGA:
#
# prioridadColaPrioridad -> ColPrioridad
# cantidadPalabraClaveEnArticulo -> Deposito
# identificarColecciones -> OperacionesDeposito

# variables a editar
CASOS=(00 01 02 03 04 05 06 A B C D E F)

ENTREGAR="ABB_T.cpp Cola.cpp ColaPrioridad.cpp Deposito.cpp OperacionesDeposito.cpp ListaOrd.cpp Pila.cpp"

ARCH_ENTREGA=Reentrega2.tar.gz
LOG_ENTREGA=entrega.log

rm -f $ARCH_ENTREGA $LOG_ENTREGA
rm -f test/*.sal test/*.diff *.o Principal

g++ -g -Wall -Werror -o Principal $ENTREGAR Principal.cpp

for caso in ${CASOS[@]}; do \
	./Principal < test/Caso$caso.in > test/Caso$caso.sal; \
	echo $caso
	diff -Z test/Caso$caso.out test/Caso$caso.sal > test/Caso$caso.diff; \
done

if [ "${#CASOS[@]}" -eq 0 ]; then
	echo No hay casos de prueba
else
	echo Debe haber ${#CASOS[@]} archivos .sal
	ls -lgG  test/*.sal
	echo
	echo Debe haber ${#CASOS[@]} archivos .diff de tamanio 0
	ls -lgG -o test/*.diff
fi

# rm -f md5.log
# for i in $ENTREGAR; do
# 	md5sum $i >> md5.log ;
# done

# echo -n "Desea generar el archivo de entrega? (S/N): "
# read entrega
# if [ $entrega = "S" ] || [ $entrega = "s" ]; then
# 	echo
# 	echo "Modulos:"
# 	tar zcvf $ARCH_ENTREGA $ENTREGAR
# 	echo
# 	echo "Archivo a entregar:"
# 	(ls -lgG $ARCH_ENTREGA; md5sum $ARCH_ENTREGA) | tee $LOG_ENTREGA
# fi
