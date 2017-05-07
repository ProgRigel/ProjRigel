using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    public abstract class Singleton<T> where T: new()
    {
        public static T Inst
        {
            get
            {
                if (mInst == null)
                    mInst = Activator.CreateInstance<T>();
                return mInst;
            }
        }
        private static T mInst;
    }
}
