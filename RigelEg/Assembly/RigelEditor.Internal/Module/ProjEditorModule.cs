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

        }

        [MainMenuItem("File", "New")]
        private static void MenuItem_File_New()
        {
            Console.WriteLine("newproj");
        }
    }
}
