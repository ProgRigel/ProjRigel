//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;

//namespace RigelEditor.Internal
//{
//    public class EditorGUIUtil
//    {
//        internal static bool _onGUIState = false;

//        private class MsgData
//        {
//            public string Title{ get; set; }
//            public string Info { get; set; }
//            public Action<bool> Callback { get; set; }
//        }

//        private static Stack<MsgData> _StackMsgData = new Stack<MsgData>();

//        public static bool ShowModalMessageBox(string title,string info,Action<bool> callback)
//        {
//            if (_onGUIState) return false;
//            MsgData msg = new MsgData() { Title = title, Info = info, Callback = callback };
//            _StackMsgData.Push(msg);
//            return true;
//        }


//        internal static void onGUI()
//        {
//            //MsgBox
//            {
//                if(_StackMsgData.Count != 0)
//                {
//                    var msg = _StackMsgData.Peek();
//                    int ret= EditorGUI.ModalMessageBox(msg.Title, msg.Info);
//                    if(ret != 0)
//                    {
//                        _StackMsgData.Pop();
//                        if (msg.Callback != null) msg.Callback.Invoke(ret == 1);
//                    }
                    
//                }
//            }
            
//        }
//    }
//}
