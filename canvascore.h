#ifndef CANVASCORE_H
#define CANVASCORE_H

#define CANVAS_SIZE_BUFFER 4

typedef struct{
    int x,y;
}CanvasPoint;

typedef struct{
    unsigned int size;
    CanvasPoint buffer[CANVAS_SIZE_BUFFER];
    CanvasPoint *lastPoint;
    unsigned int nelem;
}CanvasPointBuffer;

/**
 * @brief CanvasCoreInit
 * @return bool true quando termina de executar.
 */
bool CanvasCoreInit();

/**
Retorna True se foi o ultimo ponto inserido
Retorna False se nao foi o ultimo ponto
*/
bool CanvasBufferAddPoint(CanvasPoint p);

/**
 * @brief CanvasBufferGetPoints
 * @param v - caso jah tenha um vetor alocado use esta funçao
 */
void CanvasBufferGetPoints(CanvasPoint *v);

/**
 * @brief CanvasBufferGetPoints
 * Use CANVAS_BUFFER_NELENS para ter o tamanho do vetor. Se inserir alguem, deve rodar novamente essa funçao.
 * @return Um vetor com os pontos que estao no buffer ate o momento;
 */
CanvasPoint *CanvasBufferGetPoints();

/**
 * @brief getCanvasBuffer
 * @return retorna o CANVASBUFFER
 */
CanvasPointBuffer *getCanvasBuffer();

/**
 * @brief CanvasBufferReset
 * Esvazia o buffer
 */
void CanvasBufferReset();


/**
 * @brief CanvasBufferNelem
 * @return numero de pontos que estao no buffer;
 */
unsigned int CanvasBufferNelem();


#endif // CANVASCORE_H
