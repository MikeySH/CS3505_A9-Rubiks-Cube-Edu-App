/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "cube3Dwidget.h"

#include <QMouseEvent>

#include <cmath>
#include <iostream>
using namespace std;



Cube3DWidget::~Cube3DWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

void Cube3DWidget::keyPressEvent(QKeyEvent *event){
    if( event->key() == Qt::Key_Right ){
        angularSpeed = 2;
        rotateCubeRight();
    }
    else if( event->key() == Qt::Key_Left ){
        angularSpeed = 2;
        rotateCubeLeft();
        }
    else if( event->key() == Qt::Key_Space ){
        angularSpeed = 2;
        flipCube();
    }
}

//! [1]
void Cube3DWidget::timerEvent(QTimerEvent *)
{
   //  Decrease angular speed (friction)
    angularSpeed *= .90;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        rotation = QQuaternion::slerp(rotation, startingPosition, 0.1);
        update();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
        update();
    }
}
//! [1]

void Cube3DWidget::initializeGL()
{
    initializeOpenGLFunctions();
   // glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
    glClearColor(.92, .92, .92, 1);

    initShaders();
    initTextures();

    //! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    //! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

    // start cube at 3-sided view
    startingPosition = QQuaternion::fromEulerAngles(QVector3D(30,-54.7356,-35.2644));
    rotation = startingPosition;
}

//! [3]
void Cube3DWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void Cube3DWidget::initTextures()
{
    // Load cube.png image
    //texture = new QOpenGLTexture(QImage(":/me.png").mirrored());

    if(cubeImage.isNull()){
        texture = new QOpenGLTexture(QImage(":/cube.png"));
    }
    else {
        texture = new QOpenGLTexture(cubeImage);
    }
    //texture = new QOpenGLTexture(cubeImage.mirrored());


    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void Cube3DWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void Cube3DWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    //! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    //! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
}

void Cube3DWidget::setNewImage(QImage newimg){
    this->cubeImage = newimg;
    initTextures();
    update();
}


/*!
 * \brief MainWidget::resetCubePos Resets the cube to its starting position when reset button is pressed.
 */
void Cube3DWidget::resetCubePos(){
    rotation = startingPosition;
    angularSpeed = 0;
    update();
}

/*!
 * \brief rotateCubeLeft rotates current cube fully left
 */
void Cube3DWidget::rotateCubeLeft(){
    rotateCubeDown();
    for(int i =0 ; i<2 ; i++){
        rotateRightBy90();
    }
    rotateCubeUp();
}

/*!
 * \brief rotateCubeLeft rotates current cube fully right
 */
void Cube3DWidget::rotateCubeRight(){
   for(int i =0 ; i<3; i++)
       rotateCubeLeft();
}

/*!
 * \brief MainWidget::rotateRightBy90 rotates rubix from face to face - or 90 degrees
 */
void Cube3DWidget::rotateRightBy90(){
    rotationAxis = (QVector3D(0,-1,0)).normalized();
    int angle = -45;
    // Update rotation
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
    update();
}

/*!
 * \brief MainWidget::flipCube defines how to flip cube
 */
void Cube3DWidget::flipCube(){
    for(int i =0 ; i<4 ; i++){
         rotateCubeDown();
    }
}

/*!
 * \brief MainWidget::rotateCubeUp rotates rubix up
 */
void Cube3DWidget::rotateCubeUp(){
    rotationAxis = (QVector3D(1,0,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, 45) * rotation;
    update();
}

/*!
 * \brief MainWidget::rotateCubeDown rotates rubix down
 */
void Cube3DWidget::rotateCubeDown(){
    rotationAxis = (QVector3D(-1,0,0)).normalized();
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, 45) * rotation;
    update();
}
