using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    [AttributeUsage(AttributeTargets.Method,AllowMultiple = false,Inherited =false)]
    public class MainMenuItem :Attribute
    {
        public string Catagory;
        public string Item;
        public MainMenuItem(string catagory,string item)
        {
            Catagory = catagory;
            Item = item;
        }
    }
}
