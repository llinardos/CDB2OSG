/* Copyright (C) 2014-2016 Leandro Linardos, Buenos Aires, Argentina
 *
 * This file is part of CDB2OSG.
 *
 * CDB2OSG is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 */

#ifndef UTILS
#define UTILS

#include <osgDB/ReadFile>
#include <osg/TextureRectangle>
#include <osg/TexMat>

class Utils {
public:
    Utils() { }

    virtual ~Utils() { }

    static osgText::Text *newText(std::string string, osg::Vec4 color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                  float fontSize = 10) {
        osgText::Font *font = osgText::readFontFile("res/fonts/arial.ttf");

        osgText::Text *text = new osgText::Text;
        text->setFont(font);
        text->setColor(color);
        text->setCharacterSize(fontSize);
        text->setDataVariance(osg::Object::DYNAMIC);

        // the default layout is left to right, typically used in languages
        // originating from europe such as English, French, German, Spanish etc..
        text->setLayout(osgText::Text::LEFT_TO_RIGHT);

        text->setText(string);
        return text;
    }

    static osg::Node *newNodeWithText(osgText::Text *text, float windowWidth, float windowHeight, float margin) {
        osg::Geode *geode = new osg::Geode;

        text->setPosition(osg::Vec3(margin, windowHeight - margin, 0.0f));
        geode->addDrawable(text);

        osg::Camera *camera = new osg::Camera;
        camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
//		camera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
        camera->setProjectionMatrixAsOrtho2D(0, windowWidth, 0, windowHeight);
        camera->setViewMatrix(osg::Matrix::identity());
        camera->setClearMask(GL_DEPTH_BUFFER_BIT);
        camera->addChild(geode);
        camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

        return camera;
    }

    static void addCylinderBetweenPoints(osg::Vec3 StartPoint, osg::Vec3 EndPoint, float radius,
                                         osg::Vec4 CylinderColor, osg::Group *pAddToThisGroup) {
        osg::Vec3 center;
        float height;

        osg::ref_ptr<osg::Cylinder> cylinder;
        osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable;
        osg::ref_ptr<osg::Material> pMaterial;
        osg::ref_ptr<osg::Geode> geode;

        height = (StartPoint - EndPoint).length();
        center = osg::Vec3((StartPoint.x() + EndPoint.x()) / 2, (StartPoint.y() + EndPoint.y()) / 2,
                           (StartPoint.z() + EndPoint.z()) / 2);

        // This is the default direction for the cylinders to face in OpenGL
        osg::Vec3 z = osg::Vec3(0, 0, 1);

        // Get diff between two points you want cylinder along
        osg::Vec3 p = (StartPoint - EndPoint);

        // Get CROSS product (the axis of rotation)
        osg::Vec3 t = z ^p;

        // Get angle. length is magnitude of the vector
        double angle = acos((z * p) / p.length());

        //   Create a cylinder between the two points with the given radius
        cylinder = new osg::Cylinder(center, radius, height);
        cylinder->setRotation(osg::Quat(angle, osg::Vec3(t.x(), t.y(), t.z())));

        //   A geode to hold our cylinder
        geode = new osg::Geode;
        cylinderDrawable = new osg::ShapeDrawable(cylinder);
        cylinderDrawable->setColor(CylinderColor);
        geode->addDrawable(cylinderDrawable);

        //   Add the cylinder between the two points to an existing group
        pAddToThisGroup->addChild(geode);
    }

    static void addConeBetweenPoints(osg::Vec3 StartPoint, osg::Vec3 EndPoint, float radius, osg::Vec4 CylinderColor,
                                     osg::Group *pAddToThisGroup) {
        osg::Vec3 center;
        float height;

        osg::ref_ptr<osg::Cone> cylinder;
        osg::ref_ptr<osg::ShapeDrawable> cylinderDrawable;
        osg::ref_ptr<osg::Material> pMaterial;
        osg::ref_ptr<osg::Geode> geode;

        height = (StartPoint - EndPoint).length();
        center = osg::Vec3((StartPoint.x() + EndPoint.x()) / 2, (StartPoint.y() + EndPoint.y()) / 2,
                           (StartPoint.z() + EndPoint.z()) / 2);

        // This is the default direction for the cylinders to face in OpenGL
        osg::Vec3 z = osg::Vec3(0, 0, 1);

        // Get diff between two points you want cylinder along
        osg::Vec3 p = (StartPoint - EndPoint);

        // Get CROSS product (the axis of rotation)
        osg::Vec3 t = z ^p;

        // Get angle. length is magnitude of the vector
        double angle = acos((z * p) / p.length());

        //   Create a cylinder between the two points with the given radius
        cylinder = new osg::Cone(center, radius, height);
        cylinder->setRotation(osg::Quat(angle, osg::Vec3(t.x(), t.y(), t.z())));

        //   A geode to hold our cylinder
        geode = new osg::Geode;
        cylinderDrawable = new osg::ShapeDrawable(cylinder);
        cylinderDrawable->setColor(CylinderColor);
        geode->addDrawable(cylinderDrawable);

        //   Add the cylinder between the two points to an existing group
        pAddToThisGroup->addChild(geode);
    }

    static void addSphere(osg::Vec3d center, double radius, osg::Group *container) {
        osg::Sphere *unitSphere = new osg::Sphere(center, radius);
        osg::ShapeDrawable *unitSphereDrawable = new osg::ShapeDrawable();
        unitSphereDrawable->setShape(unitSphere);
        osg::Geode *unitSphereGeode = new osg::Geode();
        unitSphereGeode->addDrawable(unitSphereDrawable);
        container->addChild(unitSphereGeode);
    }

    static osg::Geode *createRectangle(bool centered = false) {
        osg::Vec3 top_left;
        osg::Vec3 bottom_left;
        osg::Vec3 bottom_right;
        osg::Vec3 top_right;

        if (centered) {
            top_left = osg::Vec3(-0.5, 0.5, 0);
            bottom_left = osg::Vec3(-0.5, -0.5, 0);
            bottom_right = osg::Vec3(0.5, -0.5, 0);
            top_right = osg::Vec3(0.5, 0.5, 0);
        } else {
            top_left = osg::Vec3(0, 1, 0);
            bottom_left = osg::Vec3(0, 0, 0);
            bottom_right = osg::Vec3(1, 0, 0);
            top_right = osg::Vec3(1, 1, 0);
        }
        // create geometry
        osg::Geometry *geom = new osg::Geometry;

        osg::Vec3Array *vertices = new osg::Vec3Array(4);
        (*vertices)[0] = top_left;
        (*vertices)[1] = bottom_left;
        (*vertices)[2] = bottom_right;
        (*vertices)[3] = top_right;
        geom->setVertexArray(vertices);

        osg::Vec2Array *texcoords = new osg::Vec2Array(4);
        (*texcoords)[0].set(0.0f, 0.0f);
        (*texcoords)[1].set(1.0f, 0.0f);
        (*texcoords)[2].set(1.0f, 1.0f);
        (*texcoords)[3].set(0.0f, 1.0f);
        geom->setTexCoordArray(0, texcoords);

        osg::Vec3Array *normals = new osg::Vec3Array(1);
        (*normals)[0].set(0.0f, -1.0f, 0.0f);
        geom->setNormalArray(normals, osg::Array::BIND_OVERALL);

        osg::Vec4Array *colors = new osg::Vec4Array(1);
        (*colors)[0].set(1.0f, 1.0f, 1.0f, 1.0f);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

        // disable display list so our modified tex coordinates show up
        geom->setUseDisplayList(false);

        // install 'update' callback
        osg::Geode *geode = new osg::Geode;
        geode->addDrawable(geom);

        return geode;
    }

    static void setTextureOnGeode(std::string string, osg::Geode *geode) {
        // load image
        osg::Image *img = osgDB::readImageFile(string);
        // setup texture
        osg::TextureRectangle *texture = new osg::TextureRectangle(img);
        osg::TexMat *texmat = new osg::TexMat;
        texmat->setScaleByTextureRectangleSize(true);
        // setup state
        osg::StateSet *state = geode->getDrawable(0)->getOrCreateStateSet();
        state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
        state->setTextureAttributeAndModes(0, texmat, osg::StateAttribute::ON);
        state->setMode(GL_BLEND, osg::StateAttribute::ON);
        // turn off lighting
        state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    }

};

#endif
