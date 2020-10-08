#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Shape : public IShape {
    Size mSize;
    Point mPosition;
    shared_ptr<ITexture> mTexture;

public:
    ShapeType mShapeType;

public:
    void SetPosition(Point point) override {
        mPosition = point;
    }

    Point GetPosition() const override {
        return mPosition;
    }

    void SetSize(Size size) override {
        mSize = size;
    }

    Size GetSize() const override {
        return mSize;
    }

    void SetTexture(shared_ptr<ITexture> texture) override {
        mTexture = texture;
    }

    ITexture *GetTexture() const override {
        return mTexture.get();
    }

    // Рисует фигуру на указанном изображении
    void Draw(Image &image) const override {
        for (int i = mPosition.y; i < mPosition.y + mSize.height; ++i) {
            for (int j = mPosition.x; j < mPosition.x + mSize.width; ++j) {
                if (i >= 0 && i < image.size() && j >= 0 && j < image[0].size()) {
                    Point point = Point{j - mPosition.x, i - mPosition.y};
                    Image texture;
                    if (mTexture) {
                        texture = mTexture->GetImage();
                    } else {
                        texture = Image(mSize.height, string(mSize.width, '.'));
                    }
                    if (mShapeType == ShapeType::Rectangle ||
                        (mShapeType == ShapeType::Ellipse && IsPointInEllipse(point, mSize))) {
                        if (point.y < texture.size() && point.x < texture[point.y].size()) {
                            image[i][j] = texture[point.y][point.x];
                        } else {
                            image[i][j] = '.';
                        }
                    }
                }
            }
        }
    }
};

class Rectangle : public Shape {
public:
    Rectangle() {
        mShapeType = ShapeType::Rectangle;
    }

    unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(*this);
    }
};

class Ellipse : public Shape {
public:
    Ellipse() {
        mShapeType = ShapeType::Ellipse;
    }

    unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(*this);
    }
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Ellipse:
            return make_unique<Ellipse>();
        case ShapeType::Rectangle:
            return make_unique<Rectangle>();
    }
}
