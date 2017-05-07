using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RigelCore;

namespace RigelEditor.Internal
{
    public static class EditorGUI
    {
        public static void Text(string text)
        {
            RigelEditorGUI.Text(text);
        }
        public static void TextColored(string text, float r, float g, float b, float a)
        {
            RigelEditorGUI.TextColored(text, r, g, b, a);
        }

        public static void TextDisabled(string text)
        {
            RigelEditorGUI.TextDisabled(text);
        }
        public static void TextWrapped(string text)
        {
            RigelEditorGUI.TextWrapped(text);
        }
        public static void LabelText(string label,string text)
        {
            RigelEditorGUI.LabelText(label, text);
        }
        public static void Bullet()
        {
            RigelEditorGUI.Bullet();
        }

        public static void BulletText(string text)
        {
            RigelEditorGUI.BulletText(text);
        }
        public static bool Button(string text)
        {
            return RigelEditorGUI.Button(text);
        }
        public static bool Button(string text,float with,float height)
        {
            return RigelEditorGUI.Button(text, with, height);
        }

        //menu bar
        internal static void BeginMainMenuBar()
        {
            RigelEditorGUI.BeginMainMenuBar();
        }
        internal static void EndMainMenuBar()
        {
            RigelEditorGUI.EndMainMenuBar();
        }
        internal static bool BeginMenu(string label)
        {
            return RigelEditorGUI.BeginMenu(label);
        }
        internal static void EndMenu(string label)
        {
            RigelEditorGUI.EndMenu();
        }
        internal static bool MenuItem(string label)
        {
            return RigelEditorGUI.MenuItem(label);
        }

    }
}
