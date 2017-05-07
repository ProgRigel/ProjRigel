using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace RigelEditor.Internal
{
    internal class EditorModuleManager:Singleton<EditorModuleManager>
    {
        public Dictionary<Type, EditorModule> mModules;

        private Dictionary<string, Dictionary<MainMenuItem, MethodInfo>> mMainMenuBarItems;

        public Dictionary<string, Dictionary<MainMenuItem, MethodInfo>> MainMenuBar
        {
            get { return mMainMenuBarItems; }
        }




        public EditorModuleManager()
        {
            mModules = new Dictionary<Type, EditorModule>();
            mMainMenuBarItems = new Dictionary<string, Dictionary<MainMenuItem, MethodInfo>>();
        }

        public void LoadModuleFromAssembly(Assembly assembly)
        {
            var types = assembly.GetTypes();
            foreach (var t in types)
            {
                if (t.BaseType == typeof(EditorModule))
                {
                    EditorModule module = Activator.CreateInstance(t) as EditorModule;
                    if (module == null) continue;
                    mModules.Add(t, module);

                    //menuitemm
                    var methods = t.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
                    foreach(var method in methods)
                    {
                        if (!Attribute.IsDefined(method, typeof(MainMenuItem))) continue;
                        MainMenuItem menuItemAttr = MainMenuItem.GetCustomAttribute(method, typeof(MainMenuItem)) as MainMenuItem;
                        if (menuItemAttr == null) continue;

                        Console.WriteLine(method.Name);

                        Dictionary<MainMenuItem, MethodInfo> menuItemCata;
                        if (!mMainMenuBarItems.ContainsKey(menuItemAttr.Catagory))
                        {
                            menuItemCata = new Dictionary<MainMenuItem, MethodInfo>();
                            mMainMenuBarItems.Add(menuItemAttr.Catagory,menuItemCata);
                        }
                        else
                        {
                            menuItemCata = mMainMenuBarItems[menuItemAttr.Catagory];
                        }
                            

                        menuItemCata.Add(menuItemAttr, method);
                    }
                }
            }

        }
    }
}
