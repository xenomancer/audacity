/*!********************************************************************

  Audacity: A Digital Audio Editor

  @file LoadLV2.h
  @brief Defines the module to handle the LV2 effect protocol

  Audacity(R) is copyright (c) 1999-2008 Audacity Team.
  License: GPL v2 or later.  See License.txt.

*********************************************************************/

#ifndef LV2EFFECTSMODULE_H
#define LV2EFFECTSMODULE_H

#include <memory>

#include "lilv/lilv.h"

#include "PluginProvider.h"

///////////////////////////////////////////////////////////////////////////////
//
// LV2EffectsModule
//
///////////////////////////////////////////////////////////////////////////////

class LV2EffectsModule final : public PluginProvider
{
public:
   LV2EffectsModule();
   virtual ~LV2EffectsModule();

   // ComponentInterface implementation

   PluginPath GetPath() const override;
   ComponentInterfaceSymbol GetSymbol() const override;
   VendorSymbol GetVendor() const override;
   wxString GetVersion() const override;
   TranslatableString GetDescription() const override;

   // PluginProvider implementation

   bool Initialize() override;
   void Terminate() override;
   EffectFamilySymbol GetOptionalFamilySymbol() override;

   const FileExtensions &GetFileExtensions() override;
   FilePath InstallPath() override { return {}; }

   void AutoRegisterPlugins(PluginManagerInterface & pm) override;
   PluginPaths FindModulePaths(PluginManagerInterface & pm) override;
   unsigned DiscoverPluginsAtPath(
      const PluginPath & path, TranslatableString &errMsg,
      const RegistrationCallback &callback)
         override;

   bool CheckPluginExist(const PluginPath& path) const override;

   std::unique_ptr<ComponentInterface>
      LoadPlugin(const PluginPath & path) override;

   // LV2EffectModule implementation

private:
   static const LilvPlugin *GetPlugin(const PluginPath & path);
};

#endif
