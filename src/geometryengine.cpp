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

#include "geometryengine.h"

struct VertexData
{
    QVector3D position;
    QVector3D color;
    QVector2D uv;
};

// Vertices of a cube 1X1
const int nbrVertices = 8;
VertexData vertices[] = {
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f, 0.0f), QVector2D(0.0f, 0.0f)},
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(0.0f, 1.0f, 0.0f), QVector2D(1.0f, 0.0f)},
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(0.0f, 0.0f, 1.0f), QVector2D(0.0f, 1.0f)},
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 1.0f, 0.0f), QVector2D(1.0f, 1.0f)},
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f, 1.0f), QVector2D(0.0f, 0.0f)},
    {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f, 1.0f), QVector2D(1.0f, 0.0f)},
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 1.0f, 1.0f), QVector2D(0.0f, 1.0f)},
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f, 1.0f), QVector2D(1.0f, 1.0f)},
};



// Faces of the cube
const int nbrIndices = 36;
GLushort indices[] = {
    3,6,7,
    7,5,3,
    2,7,4,
    5,7,2,
    6,1,7,
    1,4,7,
    2,4,0,
    4,1,0,
    5,2,0,
    0,3,5,
    0,1,6,
    6,3,0
};


GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initGeometry()
{
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();


    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for uv coordinates
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex uv coordinate
    int uvLocation = program->attributeLocation("uv");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(/*GL_POINTS*/GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}
