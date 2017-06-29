#ifndef RENDERBATCH_H
#define RENDERBATCH_H
#include "iostream"
#include "GraphicsComponent.h"
class RenderBatch  : public sf::Drawable, public sf::Transformable

{
    public:
        RenderBatch();
        virtual ~RenderBatch();
        void setBatchTexture(sf::Image i);
        void addQuad(BatchQuad q);
        void batchQuads();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    protected:
    private:
        sf::Texture batchTexture;
        std::vector<BatchQuad> quadList;
        sf::VertexArray batch_vertexArray;


};

#endif // RENDERBATCH_H
