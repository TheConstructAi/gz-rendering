/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IGNITION_RENDERING_OGRE_OGREUNIFORMMATERIALAPPLICATOR_HH_
#define IGNITION_RENDERING_OGRE_OGREUNIFORMMATERIALAPPLICATOR_HH_

#include <vector>

#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/Util.hh"

namespace ignition
{
  namespace rendering
  {
    /// \brief Causes all objects in a scene to be rendered with the same
    /// material when rendered by a given RenderTarget.
    /// \internal
    ///
    /// On construction it registers as an Ogre::RenderTargetListener
    /// on the provided Ogre::RenderTarget, and sets the material scheme name
    /// to a value that is unlikely to exist.
    /// When the target is about to be rendered it adds itself as an
    /// Ogre::MaterialManager::Listener.
    /// Every time ogre tries to get a technique for a material it will call
    /// handleSchemeNotFound which returns the first supported technique on the
    /// material provided to this class's constructor.
    class IGNITION_VISIBLE OgreRenderTargetMaterial :
      public Ogre::RenderTargetListener,
      public Ogre::MaterialManager::Listener
    {
      /// \brief constructor
      /// \param[in] _scene the scene manager responsible for rendering
      /// \param[in] _renderTarget the RenderTarget this should apply to
      /// \param[in] _material the material to apply to all renderables
      public: OgreRenderTargetMaterial(Ogre::SceneManager *_scene,
          Ogre::RenderTarget *_renderTarget, Ogre::Material *_material);

      /// \brief destructor
      public: ~OgreRenderTargetMaterial();

      /// \brief Callback when a render target is about to be rendered
      private: virtual void preRenderTargetUpdate(
          const Ogre::RenderTargetEvent &_evt) override;

      /// \brief Callback when a render target is finisned being rendered
      private: virtual void postRenderTargetUpdate(
          const Ogre::RenderTargetEvent &_evt) override;

      /// \brief Ogre callback that assigned same material to all renderables
      public: virtual Ogre::Technique *handleSchemeNotFound(
                  uint16_t _schemeIndex, const Ogre::String &_schemeName,
                  Ogre::Material *_originalMaterial, uint16_t _lodIndex,
                  const Ogre::Renderable *_rend) override;

      /// \brief scene manager responsible for rendering
      private: Ogre::SceneManager *scene;

      /// \brief render target that should see a uniform material
      private: Ogre::RenderTarget *renderTarget;

      /// \brief material that should be applied to all objects
      private: Ogre::Material *material;

      /// \brief name of the material scheme used by this applicator
      private: Ogre::String schemeName;
    };
  }
}

#endif