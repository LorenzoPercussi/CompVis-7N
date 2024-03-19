#include <stdio.h>
#include <stdint.h> // Para tipos de dados inteiros de tamanho fixo
#include <stdlib.h> // Para funções de alocação de memória

// Estrutura para o cabeçalho do arquivo BMP
#pragma pack(push, 1) // Garante que a estrutura seja armazenada de forma compacta na memória
typedef struct {
    char assinatura[2];     // Assinatura do arquivo ("BM" para BMP)
    uint32_t tamArq;     // Tamanho total do arquivo em bytes
    uint16_t reservado1;    // Reservado; deve ser zero
    uint16_t reservado2;    // Reservado; deve ser zero
    uint32_t offset;   // Offset para os dados da imagem
} BMPHeader;
#pragma pack(pop)

// Estrutura para o cabeçalho da imagem BMP
#pragma pack(push, 1)
typedef struct {
    uint32_t tamCabecalho;      // Tamanho do cabeçalho do bitmap em bytes
    int32_t largura;            // Largura da imagem em pixels
    int32_t altura;           // Altura da imagem em pixels
    uint16_t planos;          // Número de planos de cores (sempre 1)
    uint16_t profundidade;        // Profundidade de bits por pixel
    uint32_t compressao;     // Tipo de compressão utilizada
    uint32_t tamImagem;       // Tamanho da imagem em bytes
    int32_t pixelsx;  // Resolução horizontal em pixels por metro
    int32_t pixelsy;  // Resolução vertical em pixels por metro
    uint32_t ncores;      // Número de cores na paleta de cores
    uint32_t ncores_importantes; // Número de cores importantes (geralmente ignorado)
} BMPInfoHeader;
#pragma pack(pop)

int main() {
    // Abre o arquivo BMP para leitura binária
    FILE *file = fopen("tucano.bmp", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê o cabeçalho do arquivo BMP
    BMPHeader fileHeader;
    fread(&fileHeader, sizeof(BMPHeader), 1, file);

    // Verifica a assinatura do arquivo BMP
    if (fileHeader.assinatura[0] != 'B' || fileHeader.assinatura[1] != 'M') {
        printf("Arquivo não é um BMP válido\n");
        fclose(file);
        return 1;
    }

    // Lê o cabeçalho da imagem BMP
    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Exibe as informações do arquivo BMP
    printf("Assinatura: %c%c\n", fileHeader.assinatura[0], fileHeader.assinatura[1]);
    printf("Tamanho do arquivo: %u bytes\n", fileHeader.tamArq);
    printf("Offset dos dados da imagem: %u bytes\n", fileHeader.offset);
    printf("Tamanho do cabeçalho do bitmap: %u bytes\n", infoHeader.tamCabecalho);
    printf("Largura: %d pixels\n", infoHeader.largura);
    printf("Altura: %d pixels\n", infoHeader.altura);
    printf("Profundidade de bits por pixel: %u bits\n", infoHeader.profundidade);
    printf("Tamanho da imagem: %u bytes\n", infoHeader.tamImagem);
    // Mais informações podem ser exibidas conforme necessário

    // Fecha o arquivo
    fclose(file);

    return 0;
}
