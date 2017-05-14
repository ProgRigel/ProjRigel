using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using RigelEditor.Internal.Util;
using System.Reflection;

using RigelCore;
namespace RigelEditor.Internal
{
    [AttributeUsage(AttributeTargets.Class,AllowMultiple = false,Inherited = false)]
    class RigelInternalAttribute : IntercreptAttribute
    {
        private static Assembly mTargetAssembly;
        private static Type mType;
        private static Type mTarType;

        private static Dictionary<MethodBase, MethodInfo> mMethodMap;
        private static bool mStaticMode;

        public RigelInternalAttribute( Type t, string typename, bool staticmode = true) : this(null,t,typename,staticmode)
        {

        }

        public RigelInternalAttribute(Assembly assembly,Type t,string typename,bool staticmode = true):base("RigelInternal")
        {
            mTargetAssembly = assembly ?? Assembly.GetAssembly(typeof(RigelCore.RigelEditorApp));
            mType = t;
            mStaticMode = staticmode;

            InitReflection(typename);
        }

        private void InitReflection(string typename)
        {
            Debug.Log("start reflection");
            mMethodMap = new Dictionary<MethodBase, MethodInfo>();

            if (mTargetAssembly == null)
            {
                Debug.Log("reflect null");
                return;
            }
            if(mTarType == null)
            {
                var ts = mTargetAssembly.GetTypes();

                Debug.Log(typeof(RigelCore.RigelAPI));
                Debug.Log(mTargetAssembly.GetName().Name);
                typename = typename ?? mType.Name;
                typename = mTargetAssembly.GetName().Name + "." + typename;
                mTarType = mTargetAssembly.GetType(typename);
                if (mTarType == null)
                {
                    Debug.Log("reflect type null " + typename);
                    return;
                }
                
            }

            MethodInfo[] methods = mType.GetMethods(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);

            foreach(var m in methods)
            {
                mMethodMap.Add(m, null);
            }

            methods = mTarType.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);

            List<MethodBase> tempList = new List<MethodBase>();
            List<MethodBase> tempListBase = new List<MethodBase>(mMethodMap.Keys);
            foreach(var m in methods)
            {
                tempList.Clear();
                for(int i=0;i< tempListBase.Count;i++)
                {
                    if (tempListBase[i].Name == m.Name)
                        tempList.Add(tempListBase[i]);
                }

                foreach(var tm in tempList)
                {
                    var pm = m.GetParameters();
                    var pmb = tm.GetParameters();
                    if (pm.Length != pmb.Length) break;
                    for(int k =0;k<pm.Length;k++)
                    {
                        if (pm[k].ParameterType != pmb[k].ParameterType) break;
                    }

                    mMethodMap[tm] = m;
                }
            }

            //remove unmap data
            foreach(var m in tempListBase)
            {
                if (mMethodMap[m] == null)
                    mMethodMap.Remove(m);
            }


        }


        private void CallStatic(MethodBase method)
        {

        }

        public override void MessageStart(IMethodCallMessage msg)
        {
            if(!mMethodMap.ContainsKey(msg.MethodBase))
            {
                return;
            }
            mMethodMap[msg.MethodBase].Invoke(null, msg.Args);

        }

        public override void MessageEnd(IMethodReturnMessage msg)
        {
        }


    }
}
