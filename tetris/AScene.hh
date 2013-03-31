#ifndef					__ASCENE_HH__
# define				__ASCENE_HH__

#include				<string>
#include                                <allegro5/allegro.h>

class					AScene
{
protected:
  std::string				name_;
  bool					active_;
  bool					visible_;
  int					priority_;
  ALLEGRO_DISPLAY			*display_;
  //SceneManager			*sceneManager_;
public:
  AScene(std::string const & name = "Scene", bool active = false, bool visible = false);
  virtual ~AScene();
  std::string const &			getName() const;
  bool					getActive() const;
  bool					getVisible() const;
  int					getPriority() const;
  void					setName(std::string const name);
  void					setActive(bool active);
  void					setVisible(bool visible);
  void					setPriority(int priority);
  void					setDisplay(ALLEGRO_DISPLAY *display);
  virtual void				update(ALLEGRO_EVENT *event) = 0;
  virtual void				draw(ALLEGRO_EVENT *event) = 0;
  virtual void				input(ALLEGRO_EVENT *event) = 0;
};

#endif					// __ASCENE_HH__
