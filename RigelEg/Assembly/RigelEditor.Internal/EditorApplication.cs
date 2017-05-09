using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

using RigelCore;

namespace RigelEditor.Internal
{
    public class EditorApplication :Singleton<EditorApplication>
    {
        private Assembly mAssemblyRigelEditor;

        private RigelEditorApp _nativeApp;

        public void InitWithNative(RigelEditorApp nativeApp)
        {
            #region register callback
            _nativeApp = nativeApp;
            nativeApp.delOnGUI += NativeApp_delOnGUI;
            #endregion

            LoadMainAssembly();
            EditorModuleManager.Inst.LoadModuleFromAssembly(mAssemblyRigelEditor);
        }


        private void LoadMainAssembly()
        {
            //mAssemblyRigelEditor = Assembly.LoadFile(EditorConfig.EditorDataPath + EditorConfig.AssemblyRigelEditorName);
            mAssemblyRigelEditor = Assembly.GetAssembly(typeof(EditorApplication));
        }


        private void DrawMainMenuBar()
        {
            
            if (RigelEditorGUI.BeginMainMenuBar())
            {
                foreach (var menu in EditorModuleManager.Inst.MenuCata)
                {
                    if(RigelEditorGUI.BeginMenu(menu))
                    {
                        foreach(var item in EditorModuleManager.Inst.MenuCataDict[menu])
                        {
                            if (RigelEditorGUI.MenuItem(item.Item))
                                EditorModuleManager.Inst.MenuItemDict[item].Invoke(null, null);
                        }

                        RigelEditorGUI.EndMenu();
                    }
                }

                RigelEditorGUI.EndMainMenuBar();
            }
        }

        public void OpenProject(string projFolder,string projFile)
        {

        }

        public void NewProject()
        {

        }

        #region delegate

        private bool modelshowed = false;

        private void NativeApp_delOnGUI()
        {
            DrawMainMenuBar();

            if(!modelshowed)
            {
                if (RigelEditorGUI.ModalMessageBox("Isxxx", "xxxxxx rua"))
                    modelshowed = true;
            }
                
        }

        #endregion
    }
}
