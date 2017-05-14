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

        }

        public override void onStart()
        {
        }

        public override void onGUI()
        {
        }
    }
}
