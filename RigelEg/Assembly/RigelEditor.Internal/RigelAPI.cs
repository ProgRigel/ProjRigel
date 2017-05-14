using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RigelEditor.Internal.Util;
using RigelCore;
namespace RigelEditor.Internal
{
    [RigelInternal(typeof(Rigel),"RigelAPI")]
    public class Rigel :ContextBoundObject
    {
        private static Rigel _api;
        private static RigelEGUI _egui;
        public static Rigel API
        {
            get
            {
                if (_api == null) InitAPI();
                return _api;
            }
        }
        public static RigelEGUI EGUI { get { return _egui; } }


        private static void InitAPI()
        {
            _api = new Rigel();
            _egui = new RigelEGUI();
        }

        //GeneralAPI
        public void Test() { }
        public void TestParam(string info) { }

    }

    public class RigelEGUI
    {
        public static void Text(string text)
        {
            RigelAPI.Text(text);
        }
        public static void TextColored(string text, float r, float g, float b, float a)
        {
            RigelAPI.TextColored(text, r, g, b, a);
        }
        public static void TextDisabled(string text)
        {
            RigelAPI.TextDisabled(text);
        }
        public static void TextWrapped(string text)
        {
            RigelAPI.TextWrapped(text);
        }
        public static void LabelText(string label, string text)
        {
            RigelAPI.LabelText(label, text);
        }
        public static void Bullet()
        {
            RigelAPI.Bullet();
        }

        public static void BulletText(string text)
        {
            RigelAPI.BulletText(text);
        }
        public static bool Button(string text)
        {
            return RigelAPI.Button(text);
        }
        public static bool Button(string text, float with, float height)
        {
            return RigelAPI.Button(text, with, height);
        }

        //menu bar
        internal static bool BeginMainMenuBar()
        {
            return RigelAPI.BeginMainMenuBar();
        }
        internal static void EndMainMenuBar()
        {
            RigelAPI.EndMainMenuBar();
        }
        internal static bool BeginMenu(string label)
        {
            return RigelAPI.BeginMenu(label);
        }
        internal static void EndMenu()
        {
            RigelAPI.EndMenu();
        }
        internal static bool MenuItem(string label)
        {
            return RigelAPI.MenuItem(label);
        }

        //模态对话框 在onGUI中调用
        internal static int ModalMessageBox(string title, string info)
        {
            return RigelAPI.ModalMessageBox(title, info);
        }

        internal static void SameLine() { RigelAPI.SameLine(); }

        //window 
        internal static bool Begin(String title)
        {
            return RigelAPI.Begin(title);
        }
        internal static bool Begin(String title, int wid)
        {
            return RigelAPI.Begin(title, wid);
        }
        internal static void End()
        {
            RigelAPI.End();
        }

        internal static int EGUI_registerWindow(int windowId)
        {
            return RigelAPI.EGUI_registerWindow(windowId);
        }
    }



}
