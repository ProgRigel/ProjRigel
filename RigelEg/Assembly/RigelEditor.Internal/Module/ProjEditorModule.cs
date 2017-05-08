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
            OpenFileDialog openFile = new OpenFileDialog();
            if(openFile.ShowDialog() == DialogResult.OK)
            {
                Console.WriteLine("openfile");
            }
        }

        [MainMenuItem("File", "New")]
        private static void MenuItem_File_New()
        {
            Console.WriteLine("newproj");
        }
    }
}
