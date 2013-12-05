#include "stdlib.h"
#include "canvascore.h"

CanvasPointBuffer CANVAS_BUFFER;

/**
 * @brief CanvasCoreInit
 * @return bool true quando termina de executar.
 */
bool CanvasCoreInit(){
    CANVAS_BUFFER.size = CANVAS_SIZE_BUFFER;
    CANVAS_BUFFER.nelem = 0;
    CANVAS_BUFFER.lastPoint = NULL;
    return true;
}

/**
Retorna True se foi o ultimo ponto inserido
Retorna False se nao foi o ultimo ponto
*/
bool CanvasBufferAddPoint(CanvasPoint p){

    if(CANVAS_BUFFER.nelem == CANVAS_BUFFER.size)
        CANVAS_BUFFER.nelem = 0;
    CANVAS_BUFFER.buffer[CANVAS_BUFFER.nelem] = p;
    CANVAS_BUFFER.lastPoint = &CANVAS_BUFFER.buffer[CANVAS_BUFFER.nelem];
    (CANVAS_BUFFER.nelem)++;
    return CANVAS_BUFFER.nelem == CANVAS_BUFFER.size;
}

/**
 * @brief CanvasBufferGetPoints
 * Use CANVAS_BUFFER_NELENS para ter o tamanho do vetor. Se inserir alguem, deve rodar novamente essa funçao.
 * @return Um vetor com os pontos que estao no buffer ate o momento;
 */
CanvasPoint *CanvasBufferGetPoints(){
    CanvasPoint *v = (CanvasPoint*) malloc (sizeof(CanvasPoint)*(CANVAS_BUFFER.nelem));
    CanvasBufferGetPoints(v);
    return v;
}

/**
 * @brief CanvasBufferGetPoints
 * @param v - caso jah tenha um vetor alocado use esta funçao
 */
void CanvasBufferGetPoints(CanvasPoint *v){
    for(unsigned int i = 0; i < CANVAS_BUFFER.nelem; i++)
        v[i] = CANVAS_BUFFER.buffer[i];
}

/**
 * @brief CanvasBufferReset
 * Esvazia o buffer
 */
void CanvasBufferReset(){
    CANVAS_BUFFER.nelem = 0;
}

/**
 * @brief getCanvasBuffer
 * @return retorna o CANVASBUFFER
 */
CanvasPointBuffer *getCanvasBuffer(){
    return &CANVAS_BUFFER;
}

unsigned int CanvasBufferNelem(){
    return CANVAS_BUFFER.nelem;
}

