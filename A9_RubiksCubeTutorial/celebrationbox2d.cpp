#include "celebrationbox2d.h"
#include <QDebug>

celebrationBox2D::celebrationBox2D(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/me.png") // Make a resource file - mac executables are in a hidden folder
{

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f,38.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);


    float a = 0.5f;
        b2PolygonShape shape;
        shape.SetAsBox(a, a);
        b2FixtureDef boxFixtures;
        boxFixtures.shape = &shape;
        boxFixtures.density = 1.0f;
        boxFixtures.friction = 0.1f;
        boxFixtures.restitution = 0.99;

        b2Vec2 x(4.0f, 7.75f);
        b2Vec2 y;
        b2Vec2 deltaX(0.5625f, 1.25f);
        b2Vec2 deltaY(1.125f, 0.0f);

        for (int32 i = 0; i < 5; ++i)
        {
            y = x;

            for (int32 j = i; j < 10; ++j)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position = y;
                b2Body* body = world.CreateBody(&bd);
                body->CreateFixture(&boxFixtures);
                //b2Vec2 p(6.0f, 6.0f);
                //b2Vec2 v = -10.0f;
                body->SetLinearVelocity(y);

                y += deltaY;
            }

            x += deltaX;
        }


    connect(&timer, &QTimer::timeout, this, &celebrationBox2D::updateWorld);
    timer.start(10);
}

void celebrationBox2D::paintEvent(QPaintEvent *) {
    // Create a painter
     QPainter painter(this);


     for(b2Body *body = world.GetBodyList(); body; body = body->GetNext()) {
         b2Vec2 position = body->GetPosition();
                 painter.drawImage((int)(position.x * 25), (int)(position.y*25), image.scaled(80, 80, Qt::KeepAspectRatio));
     }

     painter.end();

}

void celebrationBox2D::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/40.0, 6, 2);

    update();
}
