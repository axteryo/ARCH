#ifndef SEQUENCEENTITY_H
#define SEQUENCEENTITY_H

#include <entity.h>


class SequenceEntity : public entity
{
    public:
        SequenceEntity(std::string e_ID, std::string e_tag,std::string t_tag,std::string sequenceType);
        virtual ~SequenceEntity();
        void update();
        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void onInitiateSequence();
    protected:
        std::string trigger_tag;

        enum sequence_type
        {
            SEQ_COMBAT,
            SEQ_NARRATIVE
        }seqType;
    private:
};

#endif // SEQUENCEENTITY_H
