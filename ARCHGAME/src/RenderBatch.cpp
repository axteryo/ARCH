#include "RenderBatch.h"

RenderBatch::RenderBatch()
{
    //ctor
    batch_vertexArray.setPrimitiveType(sf::Quads);
}

RenderBatch::~RenderBatch()
{
    //dtor
}

void RenderBatch::setBatchTexture(sf::Image i)
{
    if(!batchTexture.loadFromImage(i))
    {
        std::cout<<"Unable to load batch texture"<<std::endl;
    }
    else
    {
        batchTexture.setSmooth(false);
    }
}
void RenderBatch::addQuad(BatchQuad q)
{
    quadList.push_back(q);
}
void RenderBatch::batchQuads()
{
    batch_vertexArray.clear();
    if(!quadList.empty())
    {
        batch_vertexArray.resize(quadList.size()*4);
        int j = 0;
        for(int i = 0; i <quadList.size();++i)
        {

            sf::Vertex* quad = &batch_vertexArray[j];
            quad[j].position =quadList[i].point1;
            quad[j+1].position =quadList[i].point2;
            quad[j+2].position =quadList[i].point3;
            quad[j+3].position =quadList[i].point4;

            quad[j].texCoords = quadList[i].texPoint1;
            quad[j+1].texCoords =quadList[i].texPoint2;
            quad[j+2].texCoords =quadList[i].texPoint3;
            quad[j+3].texCoords =quadList[i].texPoint4;

            j+=2;
        }
    }
    quadList.clear();
}
void RenderBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=getTransform();
    states.texture= &batchTexture;

    target.draw(batch_vertexArray,states);
}
