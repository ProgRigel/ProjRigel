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

        private List<string> mMenuCatagory;
        private Dictionary<string, List<MainMenuItem>> mMenuCatagoryDict;
        private Dictionary<MainMenuItem, MethodInfo> mMenuItemDict;

        public List<string> MenuCata { get { return mMenuCatagory; } }
        public Dictionary<string,List<MainMenuItem>> MenuCataDict { get { return mMenuCatagoryDict; } }
        public Dictionary<MainMenuItem, MethodInfo> MenuItemDict { get { return mMenuItemDict; } }

        public EditorModuleManager()
        {
            mModules = new Dictionary<Type, EditorModule>();

            mMenuCatagory = new List<string>();
            mMenuCatagoryDict = new Dictionary<string, List<MainMenuItem>>();
            mMenuItemDict = new Dictionary<MainMenuItem, MethodInfo>();
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
                    module.onStart();
                    mModules.Add(t, module);

                    Console.WriteLine("[Module] Load " + t);

                    //menuitemm
                    var methods = t.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
                    foreach(var method in methods)
                    {
                        Console.WriteLine("[method]" + method.Name);

                        if (!Attribute.IsDefined(method, typeof(MainMenuItem))) continue;
                        MainMenuItem attr = MainMenuItem.GetCustomAttribute(method, typeof(MainMenuItem)) as MainMenuItem;
                        if (attr == null) continue;

                        Console.WriteLine(method.Name);

                        if (!mMenuCatagoryDict.ContainsKey(attr.Catagory))
                        {
                            mMenuCatagoryDict.Add(attr.Catagory, new List<MainMenuItem>());
                            mMenuCatagory.Add(attr.Catagory);
                        }
                        mMenuCatagoryDict[attr.Catagory].Add(attr);

                        mMenuItemDict.Add(attr, method);

                        
                    }
                }
            }

            //reorder
            mMenuCatagory.Sort((a, b) =>
            {
                int orderA = EditorConfig.MENU_CATA_ORDER.ContainsKey(a) ? EditorConfig.MENU_CATA_ORDER[a] : EditorConfig.MENU_CATA_ORDER_DEF;
                int orderB = EditorConfig.MENU_CATA_ORDER.ContainsKey(b) ? EditorConfig.MENU_CATA_ORDER[b] : EditorConfig.MENU_CATA_ORDER_DEF;
                return orderA.CompareTo(orderB);
            });

        }

        public void ExecModuleOnGUI()
        {
            EditorGUIUtil._onGUIState = true;
            foreach (var mod in mModules)
            {
                if (!mod.Value.Enable) continue;
                mod.Value.onGUI();
            }
            EditorGUIUtil._onGUIState = false;
        }
    }
}
