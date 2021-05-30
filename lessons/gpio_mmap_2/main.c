#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

#define GPIO 10
#define CICLOS 5

void configGPIO(volatile uint32_t *gpio_virtual, int gpio, int modo);
void valueGPIO(volatile uint32_t *gpio_virtual, int gpio, int modo);
volatile uint32_t *obtDirVirtual(off_t dirBase, int *fd);

int main()
{

        volatile uint32_t *gpio_virtual;

        int fd;
        register int i;

        gpio_virtual = obtDirVirtual(0x3f200000, &fd);

        configGPIO(gpio_virtual, GPIO, 0);
        //Se configura el BCM GPIO16 como salida
        // *(gpio + 1) = (*(gpio + 1) & ~(7 << 18)) | (1 << 18);

        for (i = 0; i < CICLOS; i++)
        {
                //Se pone en uno el GPIO 16
                valueGPIO(gpio_virtual, GPIO, 1);

                sleep(2);

                //Se pone en ceroel GPIO 16
                valueGPIO(gpio_virtual, GPIO, 0);

                // *(gpio_virtual + 10) = *(gpio_virtual + 10) | (1 << 16);

                sleep(2);
        }
        close(fd);
        return 0;
}

/*
	@brief: Esta función configura un GPIO como entrada o salida
	@param: gpio_virtual, DIreccion de la memoria virtual del gpio
	@param: gpio, Numero de GPIO a configurar
	@param: modo,0 salida, 1 entrada

*/

void configGPIO(volatile uint32_t *gpio_virtual, int gpio, int modo)
{

        int GPFSEL = gpio / 10;
        int bitRango = (gpio % 10);
        bitRango = (bitRango << 1) + bitRango;
        if (modo == 0)
                *(gpio_virtual + GPFSEL) = (*(gpio_virtual + GPFSEL) & ~(7 << bitRango)) | (1 << bitRango);
        else if (modo == 1)
                *(gpio_virtual + GPFSEL) = (*(gpio_virtual + GPFSEL) & ~(7 << bitRango));
}

void valueGPIO(volatile uint32_t *gpio_virtual, int gpio, int valor)
{

        int bit = (gpio >> 5); //gpio/323232sd
        int GPSET = bit + 7;
        int GPCLR = bit + 10;

        int bitRango = gpio % 32;

        if (valor == 1)
                *(gpio_virtual + GPSET) = *(gpio_virtual + GPSET) | (1 << bitRango);
        else if (valor == 0)
                *(gpio_virtual + GPCLR) = *(gpio_virtual + GPCLR) | (1 << bitRango);
}

volatile uint32_t *obtDirVirtual(off_t dirBase, int *fd)
{

        volatile uint32_t *per_virtual;
        register int i;
        /* Se obtiene un manejador a la memoria física
         * /dev/mem es un device driver de caracter que contiene una imagen de la
         * memoria principal de la computadora.
         *
         * Los Bytes de direcciones en /dev/mem son interpretados como direcciones de
         * la memoria física.
         * O_RDWR - Bandera para lectura y escritura
         * O_SYNC - Bandera para sincronia. El archivo es abierto para acceso de I/O sincrono
         * Cualquier escritura en el despriptor de archivo bloqueara la llamada a proceso hasta
         * que el dato se haya escrito fisicamente.
         */

        *fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (*fd == -1)
        {
                printf("Error al abrir /dev/mem %s \n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        //Se obtiene una pagina de memoria en el espacio de direcciones virtuales
        //a partir del offset 0x3f200000. En este offset se encuentran
        //mapeados los perifericos. Consultar en el FHS en /proc/interrupts
        //El primer parametro indica que la Direccion de inicio del mapa es cero
        //El segundo parametro es el número de bytes a mapear
        //El tercer parametro indica que la pagina puede ser de lectura y escritura
        //El cuarto parametro indica que las modificaciones al mapa seran visibles a otros procesos
        //El quinto parametro es el manejador de lamemoria fisica
        //El sexto parametro es la dirección de inicio dell segmento
        per_virtual = (uint32_t *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
                                       MAP_SHARED, *fd, dirBase);

        if (per_virtual == MAP_FAILED)
        {
                printf("Error al obtener direcion virtual: %s\n", strerror(errno));
                return -1;
        }
        printf("La direccion virtual es: %x\n", per_virtual);

        return per_virtual;
}
