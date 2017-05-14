using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Remoting.Contexts;
using System.Runtime.Remoting.Proxies;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting.Services;
using System.Runtime.Remoting.Activation;

namespace RigelEditor.Internal.Util
{
    public class IntercreptAttribute : ContextAttribute, IContributeObjectSink
    {
        protected IntercreptSink mSink;

        public IntercreptAttribute(string name):base(name)
        {

        }

        public IMessageSink GetObjectSink(MarshalByRefObject obj, IMessageSink nextSink)
        {
            mSink = new IntercreptSink(nextSink,this);
            return mSink;
        }

        public virtual void MessageStart(IMethodCallMessage msg)
        {

        }

        public virtual void MessageEnd(IMethodReturnMessage msg)
        {

        }
    }


    public class IntercreptSink : IMessageSink
    {
        private IMessageSink mNextSink;
        private IntercreptAttribute mAttr;
        public IntercreptSink(IMessageSink nextsink,IntercreptAttribute attr)
        {
            mNextSink = nextsink;
            mAttr = attr;
        }
        public IMessageSink NextSink
        {
            get
            {
                return mNextSink;
            }
        }
        public IMessageCtrl AsyncProcessMessage(IMessage msg, IMessageSink replySink)
        {
            return null;
        }

        protected virtual void MessageStart(IMethodCallMessage msg)
        {
            mAttr.MessageStart(msg);
        }
        protected virtual void MessageEnd(IMethodReturnMessage msg)
        {
            mAttr.MessageEnd(msg);
        }

        public IMessage SyncProcessMessage(IMessage msg)
        {
            MessageStart(msg as IMethodCallMessage);
            IMethodReturnMessage returnmsg = null;
            returnmsg = mNextSink.SyncProcessMessage(msg) as IMethodReturnMessage;
            MessageEnd(returnmsg);
            return returnmsg;
        }
    }


}
