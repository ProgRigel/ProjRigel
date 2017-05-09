using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace RigelEditor.Internal
{
    class InfoEditorModule : EditorModule
    {
        [MainMenuItem("Help","About RigelEngine")]
        public static void MenuItemInfo()
        {

        }

        [MainMenuItem("Help", "by Yemi")]
        public static void MenuItemCopyRight()
        {
            Console.WriteLine("xxx");
            EditorGUIUtil.ShowModalMessageBox("info", "this is a messagebox", (ok) =>
            {
                EditorGUIUtil.ShowModalMessageBox("2", "t1", (ok1) => { });
            });
            EditorGUIUtil.ShowModalMessageBox("3", "txxx", (ok1) => { });
        }

        public override void onStart()
        {
        }

        public override void onGUI()
        {
            EditorGUI.Text("this is info editor module");
            EditorGUI.TextColored("GreenColor", 0.1f, 1.0f, 0.3f, 1.0f);
            EditorGUI.TextColored("GreenColor", 1.0f, 0.2f, 0.3f, 1.0f);
            EditorGUI.Bullet();
            EditorGUI.BulletText("bullet text");
            EditorGUI.LabelText("label", "content");
            if(EditorGUI.Button("Click",100f,30f))
            {
                Console.WriteLine("clicked");
            }
        }
    }
}
