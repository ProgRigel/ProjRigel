using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RigelEditor.Internal;

namespace RigelEditor
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
