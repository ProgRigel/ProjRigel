using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace RigelEditor.Internal
{
    public class ProjEditorModule :EditorModule
    {
        private static EditorProject mCurrentProj = null;

        private static int mEGUI_projInfoId;

        [MainMenuItem("File","Open")]
        private static void MenuItem_File_Open()
        {
            string projFileName = null;
            using (var openFolder = new OpenFileDialog())
            {
                openFolder.Filter = "Rigel Project (*.rigel)|*.rigel";
                openFolder.Multiselect = false;
                if (openFolder.ShowDialog() == DialogResult.OK)
                {
                    projFileName = openFolder.FileName;
                }
            }

            if (string.IsNullOrEmpty(projFileName)) return;
            FileInfo file = new FileInfo(projFileName);
            if (!file.Exists) return;

            mCurrentProj = new EditorProject(file);
        }

        [MainMenuItem("File", "New")]
        private static void MenuItem_File_New()
        {
            using (var openFolder = new FolderBrowserDialog())
            {
                //openFolder.Filter = "Rigel Project (*.rigel)|*.rigel";
                if (openFolder.ShowDialog() == DialogResult.OK)
                {

                }
            }
        }


        public override void onGUI()
        {
            if(mCurrentProj == null)
            {
                RigelEGUI.Text("Quick Start");
                if(RigelEGUI.Button("New Project"))
                {
                    MenuItem_File_New();
                }
                RigelEGUI.SameLine();
                if (RigelEGUI.Button("Open Project"))
                {
                    MenuItem_File_Open();
                }

            }

            DrawProjectInfo();

        }

        private void DrawProjectInfo()
        {
            if(mCurrentProj !=null)
            {
               
                mEGUI_projInfoId = RigelEGUI.EGUI_registerWindow(mEGUI_projInfoId);

                RigelEGUI.Begin("ProjectInfo - " + mCurrentProj.ProjectName,mEGUI_projInfoId);

                Rigel.API.Test();
                RigelEGUI.End();
            }
        }
    }

    public class EditorProject
    {
        public string ProjectName { get; private set; }
        public EditorProject(FileInfo projfile)
        {
            ProjectName = projfile.Name;
        }
    }
}
