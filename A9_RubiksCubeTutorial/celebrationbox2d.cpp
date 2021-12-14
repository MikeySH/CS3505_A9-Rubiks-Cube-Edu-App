/*
 * Jimmy Trinh && Jacob Day && Amitoj Singh && Michael Shin
 * Software Practice II, CS 3505
 * Fall 2021
 * A9: An Educational App
 */

#include "celebrationbox2d.h"

/*!
 * \brief celebrationBox2D::celebrationBox2D constructor for the celebration Box2D class.
 */
celebrationBox2D::celebrationBox2D(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/me2.png")
{

}

/*!
 * \brief celebrationBox2D::startWorld Starts the Box2D celebration screen.
 */
void celebrationBox2D::startWorld()
{
    for(b2Body *body = world.GetBodyList(); body; body = body->GetNext()) {
        world.DestroyBody(body);
    }

    disconnect(&timer, &QTimer::timeout, this, &celebrationBox2D::updateWorld);

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

    //float a = 0.5f;
    float a = 1.0f;
        b2PolygonShape shape;
        shape.SetAsBox(a, a);
        b2FixtureDef boxFixtures;
        boxFixtures.shape = &shape;
        boxFixtures.density = 1.0f;
        boxFixtures.friction = 0.1f;
        boxFixtures.restitution = 0.99;

        b2Vec2 x(18.0f, -8.0f);
        b2Vec2 y;
        b2Vec2 deltaX(0.5625f, 1.25f);
        b2Vec2 deltaY(1.125f, 0.0f);

        //Creating body's in the shape of a pyramid

        //height of pyramid
        for (int32 i = 0; i < 5; ++i)
        {
            y = x;

            //base width of pyramid
            for (int32 j = i; j < 10; ++j)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position = y;
                b2Body* body = world.CreateBody(&bd);
                body->CreateFixture(&boxFixtures);
                b2Vec2 still(1.0f, 1.0f);
                body->SetLinearVelocity(still);

                y += deltaY;
            }
            x += deltaX;
        }

    connect(&timer, &QTimer::timeout, this, &celebrationBox2D::updateWorld);
    timer.start(15);
}

/*!
 * \brief celebrationBox2D::paintEvent Paints objects
 */
void celebrationBox2D::paintEvent(QPaintEvent *)
{
     // Create a painter
     QPainter painter(this);

     //goes through all the body and draw them
     for(b2Body *body = world.GetBodyList(); body; body = body->GetNext())
     {
         b2Vec2 position = body->GetPosition();
                 painter.drawImage((int)(position.x * 25), (int)(position.y*25), image.scaled(130, 130, Qt::KeepAspectRatio));
     }

     painter.end();
}

/*!
 * \brief celebrationBox2D::updateWorld Updates world
 */
void celebrationBox2D::updateWorld()
{
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/50.0, 6, 2);

    update();
}
