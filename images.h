#ifndef _IMAGES_H
#define _IMAGES_H

#include <string>
#include <vector>

class Cargo
{
public:
    std::string content;
    std::string category;
    std::string description;
    int   quantity;
    float price;
    float mass;
    float volume;
    bool  mission;
    bool  installed;
    float functionality;
    float maxfunctionality;
    Cargo()
    {
        mass     = 0;
        volume   = 0;
        price    = 0;
        quantity = 1;
        mission  = false;
        installed = false;
        functionality = maxfunctionality = 1.0f;
    }
    Cargo( std::string name, std::string cc, float pp, int qq, float mm, float vv, float func, float maxfunc ) :
        content( name )
        , category( cc )
    {
        quantity = qq;
        price    = pp;
        mass     = mm;
        volume   = vv;
        mission  = false;
        installed = false;
        functionality = func;
        maxfunctionality = maxfunc;
    }
    Cargo( std::string name, std::string cc, float pp, int qq, float mm, float vv ) :
        content( name )
        , category( cc )
    {
        quantity = qq;
        price    = pp;
        mass     = mm;
        volume   = vv;
        mission  = false;
        installed = false;
    }
    float GetFunctionality()
    {
        return functionality;
    }
    float GetMaxFunctionality()
    {
        return maxfunctionality;
    }
    void SetFunctionality( float func )
    {
        functionality = func;
    }
    void SetMaxFunctionality( float func )
    {
        maxfunctionality = func;
    }
    void SetMissionFlag( bool flag )
    {
        this->mission = flag;
    }
    void SetPrice( float price )
    {
        this->price = price;
    }
    void SetMass( float mass )
    {
        this->mass = mass;
    }
    void SetVolume( float vol )
    {
        this->volume = vol;
    }
    void SetQuantity( int quantity )
    {
        this->quantity = quantity;
    }
    void SetContent( const std::string &content )
    {
        this->content = content;
    }
    void SetCategory( const std::string &category )
    {
        this->category = category;
    }

    bool GetMissionFlag() const
    {
        return this->mission;
    }
    const std::string& GetCategory() const
    {
        return category;
    }
    const std::string& GetContent() const
    {
        return content;
    }
    const std::string& GetDescription() const
    {
        return description;
    }
    std::string GetCategoryPython()
    {
        return GetCategory();
    }
    std::string GetContentPython()
    {
        return GetContent();
    }
    std::string GetDescriptionPython()
    {
        return GetDescription();
    }
    int GetQuantity() const
    {
        return quantity;
    }
    float GetVolume() const
    {
        return volume;
    }
    float GetMass() const
    {
        return mass;
    }
    float GetPrice() const
    {
        return price;
    }
    bool operator==( const Cargo &other ) const
    {
        return content == other.content;
    }
    bool operator<( const Cargo &other ) const
    {
        return (category == other.category) ? (content < other.content) : (category < other.category);
    }
};

#endif
