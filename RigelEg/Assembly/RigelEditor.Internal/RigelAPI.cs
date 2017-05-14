using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RigelEditor.Internal.Util;
namespace RigelEditor.Internal
{
    [RigelInternal(typeof(Rigel),"RigelAPI")]
    public class Rigel :ContextBoundObject
    {
        private static Rigel _api;
        public static Rigel API
        {
            get
            {
                if (_api == null) _api = new Rigel();
                return _api;
            }
        }


        public void Test() { }
        public void TestParam(string info) { }
    }

}
