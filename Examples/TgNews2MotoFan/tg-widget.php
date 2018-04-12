<?php
/**
 * Plugin Name: Telegram News widget for MotoFan.Ru
 * Description: A widget that displays news from MotoFan.Ru Telegram group.
 * Version: 1.0.0
 * Author: EXL
 * Author URI: http://exlmoto.ru
 */

// WordPress Widget for showing Telegram News
// License: MIT
// (c) EXL, 11-APR-2018, email: exlmotodev@gmail.com

add_action('widgets_init', 'tg_widget');

function tg_widget() {
    register_widget('TG_Widget');
}

class TG_Widget extends WP_Widget {

    function TG_Widget() {
        $widget_ops = array('classname' => 'tg_widget', 'description' => __('A widget that displays news from MotoFan.Ru Telegram group.', 'tg_widget'));
        $control_ops = array('width' => 280, 'height' => 350, 'id_base' => 'tg-widget');
        $this->WP_Widget('tg-widget', __('Tg News Widget', 'tg_widget'), $widget_ops, $control_ops);
    }

    function widget($args, $instance) {
        extract($args);

        // Our variables from the widget settings.
        $title = apply_filters('widget_title', $instance['title']);
        // $name = $instance['name'];
        $show_info = (int) isset( $instance['show_info'] ) ? $instance['show_info'] : false;

        echo $before_widget;

        // Display the widget title
        if ($title) {
            echo $before_title . $title . $after_title;
        }

        // Display telegram news posts
        global $wpdb;
        $post_cnt = ($show_info) ? 5 : 10;
        $query = 'SELECT * FROM (SELECT * FROM tg_news ORDER BY id DESC LIMIT ' . $post_cnt . ') sub ORDER BY id DESC';
        $results = $wpdb->get_results($query);
        if (sizeof($results) > 0) {
            if (!$show_info) echo '<ul>';
            foreach ($results as $post) {
                if ($show_info) {
                    echo '<script async src="https://telegram.org/js/telegram-widget.js?4" data-telegram-post="motofan_ru/' . $post->msgId . '" data-width="900px"></script>';
                } else {
                    echo '<li class="cat-item cat-item-5"><div style="font-size: 13px;">' . $post->post . '</div></li>';
                }
            }
            if (!$show_info) echo '</ul>';
        } else {
            printf('<ul><p class="cat-item cat-item-5">' . __('Пока здесь ничего нет!', 'tg_widget') . '</p></ul>');
        }
        echo $after_widget;
    }

    function update($new_instance, $old_instance) {
        $instance = $old_instance;
        // Strip tags from title and name to remove HTML
        $instance['title'] = strip_tags($new_instance['title']);
        //$instance['name'] = strip_tags( $new_instance['name'] );
        $instance['show_info'] = $new_instance['show_info'];
        return $instance;
    }

    function form($instance) {
        // Set up some default widget settings.
        $defaults = array('title' => __('Лента Telegram', 'tg_widget'), 'name' => __('Bilal Shaheen', 'tg_widget'), 'show_info' => 1);
        $instance = wp_parse_args((array)$instance, $defaults); ?>
        <p>
            <label for="<?php echo $this->get_field_id('title'); ?>"><?php _e('Заголовок:', 'tg_widget'); ?></label>
            <input id="<?php echo $this->get_field_id('title'); ?>" name="<?php echo $this->get_field_name('title'); ?>"
                   value="<?php echo $instance['title']; ?>" style="width:100%;"/>
        </p>
        <p>
            <label for="<?php echo $this->get_field_id('show_info'); ?>"><?php _e('Использовать виджеты:', 'tg_widget'); ?></label>
            <input id="<?php echo $this->get_field_id('show_info'); ?>" name="<?php echo $this->get_field_name('show_info'); ?>"
                   value="<?php echo $instance['show_info']; ?>" style="width:100%;"/>
        </p>
        <?php
        /*<p>
            <input class="checkbox" type="checkbox" <?php checked( $instance['show_info'], true ); ?> id="<?php echo $this->get_field_id( 'show_info' ); ?>" name="<?php echo $this->get_field_name( 'show_info' ); ?>" />
            <label for="<?php echo $this->get_field_id( 'show_info' ); ?>"><?php _e('Использовать виджеты?', 'tg_widget'); ?></label>
        </p>
        <p>
            <label for="<?php echo $this->get_field_id( 'name' ); ?>"><?php _e('Your Name:', 'tg_widget'); ?></label>
            <input id="<?php echo $this->get_field_id( 'name' ); ?>" name="<?php echo $this->get_field_name( 'name' ); ?>" value="<?php echo $instance['name']; ?>" style="width:100%;" />
        </p> */
    }
}
?>
