import irc.client
import sys

# Taken from the example
class IRCCat(irc.client.SimpleIRCClient):
    def __init__(self, target, msg):
        irc.client.SimpleIRCClient.__init__(self)
        self.target = target
        self.msg = msg
        
    def on_welcome(self, connection, event):
        if irc.client.is_channel(self.target):
            connection.join(self.target)
        else:
            self.send_it()

    def on_join(self, connection, event):
        self.send_it()

    def on_disconnect(self, connection, event):
        sys.exit(0)

    def send_it(self):
        self.connection.privmsg(self.target, self.msg)
        self.connection.quit("Using irc.client.py")

def usage():
    print """
    USAGE:
      > python yell_in_irc.py <channel> <msg>
    """

if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
        sys.exit(1)
        
    channel = sys.argv[1]
    msg = sys.argv[2]

    client = IRCCat(channel, msg)
    try:
        client.connect(
            server="irc.tfbnw.net",
            port=6443,
            nickname="SI_TAKEDOWN_THE_SITE",
            password=None,
            username=None,
            ircname=None,
            localaddress="",
            localport=0,
            ssl=True)
    except irc.client.ServerConnectionError, x:
        print x
        sys.exit(1)
        
    client.start()
